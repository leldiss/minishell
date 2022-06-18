/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:43:26 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/14 00:37:41 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_open2(t_execute *cmds)
{
	int	fd_pipe[2];
	int	pid;

	if (cmds->stdIn2 != 0)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		pid = fork();
		if (!pid)
		{
			write(fd_pipe[1], cmds->stdIn2, ft_strlen(cmds->stdIn2));
			close(fd_pipe[1]);
			close(fd_pipe[0]);
			free_all(cmds);
			exit(0);
		}
		close(fd_pipe[1]);
		waitpid(pid, &info->status, 0);
		dup2(fd_pipe[0], 1);
		close(fd_pipe[0]);
	}
	return (0);
}

static int	fd_open(t_execute *cmds, int fd_0, int fd_1, int *fd)
{
	if (cmds->stdIn != 0)
	{
		fd[0] = open(cmds->stdIn, O_RDONLY);
		if (fd[0] < 0)
			return (ft_error(cmds->stdIn, ": No such file or dirctory"));
		dup2(fd[0], 0);
	}
	if (ft_open2(cmds) == -1)
		return (-1);
	else
		dup2(fd_0, 0);
	if (cmds->stdOut != 0)
	{
		fd[1] = open(cmds->stdIn, O_WRONLY | O_TRUNC | O_CREAT);
		dup2(fd[1], 1);
	}
	else if (cmds->stdOut2 != 0)
	{
		fd[1] = open(cmds->stdIn2, O_WRONLY | O_APPEND | O_CREAT);
		dup2(fd[1], 1);
	}
	else
		dup2(fd_1, 1);
	return (0);
}

int	child_process(t_execute *cmds, int fd_0, int fd_1, t_pipex *pip)
{
	int	fd[2];
	int	status;

	if (fd_open(cmds, fd_0, fd_1, fd) == -1)
		return (-1);
	// builtins
	close_fd_pip(pip);
	fd_close(fd[0], fd[1], cmds);
	status = execve(cmds->arguments[0], cmds->arguments, pip->info->envp);
	free_all(cmds);
	free(pip->pid);
	pip->pid = NULL;
	free(pip->pipe_fd);
	pip->pipe_fd = NULL;
	exit(status);
}

void	parent_process(t_execute *cmds, t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i <= pip->num_pipes)
	{
		pip->pid[i] = fork();
		if (pip->pid[i] == -1)
			ft_error("Error: fork mistake", "\n");
		if (!pip->pid[i])
		{
			if (i == 0)
				child_process(cmds, pip->temp_0_fd, \
							pip->pipe_fd[i * 2 + 1], pip);
			else if (i == pip->num_pipes)
				child_process(cmds, pip->pipe_fd[(i - 1) * 2], \
							pip->temp_1_fd, pip);
			else
				child_process(cmds, pip->pipe_fd[(i - 1) * 2], \
							pip->pipe_fd[i * 2 + 1], pip);
		}
		cmds = cmds->next;
	}
}

int	pipex(t_info *info, t_execute *cmds, t_pipex *pip)
{
	int	i;

	i = -1;
	init_pip(pip);
	info->pid_child = pip->pid;
	parent_process(cmds, pip);
	close_fd(pip);
	while (++i <= pip->num_pipes)
	{
		waitpid(pip->pid[i], &info->status, 0);
		info->status = info->status % 256;
	}
	free(pip->pid);
	pip->pid = NULL;
	free(pip->pipe_fd);
	pip->pipe_fd = NULL;
	return (0);
}
