/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:23:14 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/14 20:31:37 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_error(char *cmd, char *mess)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (-1);
}

void	fd_close(int fd_0, int fd_1, t_execute *cmds)
{
	if (cmds->stdIn != 0 || cmds->stdIn2 != 0)
		close(fd_0);
	if (cmds->stdOut != 0 || cmds->stdOut2 != 0)
		close(fd_1);
}

int	ft_arg_size(t_arguments *arg)
{
	int	len;

	len = 0;
	while (arg)
	{
		++len;
		arg = arg->next;
	}
	return (len);
}

void	close_fd_pip(t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i < pip->num_pipes * 2)
		close(pip->pipe_fd[i]);
}

int	init_pip(t_pipex *pip)
{
	int	i;

	i = -1;
	pip->pipe_fd = malloc(sizeof(int) * pip->num_pipes * 2);
	if (!pip->pipe_fd)
		return (-1);
	while (++i < pip->num_pipes)
		if (pipe(pip->pipe_fd + i * 2) == -1)
			return (-1);
	pip->pid = malloc(sizeof(int) * (pip->num_pipes + 1));
	return (0);
}

int ft_arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}