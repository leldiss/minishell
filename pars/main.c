/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 13:11:54 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execute/execute.h"

void printDir()
{
	char	cwd[1024];
	char *username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	printf("%s in %s ", username, cwd);
}

char	*ft_readline(char *p)
{
	char	*s;

	s = readline(p);
	if (s)
		add_history(s);
	return (s);
}

int main(int ac, char **av, char *envp[])
{
	t_execute	*info;
	t_info		information;
	(void)ac;
	(void)av;
	char *line;

	info = first_execute();
	printDir();
	init_info(&information, envp);
	get_envp(&information, envp);
	info->info = &information;
	line = ft_readline("> ");
	start_parse(info, line);
	while (info != NULL)
	{
		printf("Command is %s\n", info->command);
		printf("Option is %s\n", info->option);
		printf("Output is %s\n", info->stdout);
		printf("Output2 is %s\n", info->stdout2);
		printf("Input is %s\n", info->stdin);
		printf("Input2 is %s\n", info->stdin2);
		info->argument = info->argument->head;
		int i = 1;
		t_arguments *kek = info->argument;
		while (kek != NULL)
		{
			printf("argument %d = %s end\n", i, kek->argument);
			i++;
			kek = kek->next;
		}
		info = info->next;		
	}
	// execute(info, &information);
	free_all(info);
	exit(0);
}
