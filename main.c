/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/07 20:36:20 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printDir()
{
	char	cwd[1024];
	char *username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	printf("%s in %s ", username, cwd);
}

int main()
{
	t_execute *info;
	char *line;

	info = first_execute();
	printDir();
	line = readline("> ");
	start_parse(info, line);
	t_execute *info2;
	info2 = info;
	info2 = info2->head;
	while (info2 != NULL)
	{
		printf("Command is %s\n", info2->command);
		printf("Option is %s\n", info2->option);
		printf("Output is %s\n", info2->stdOut);
		printf("Output2 is %s\n", info2->stdOut2);
		printf("Input is %s\n", info2->stdIn);
		printf("Input2 is %s\n", info2->stdIn2);
		info2->argument = info2->argument->head;
		int i = 1;
		t_arguments *kek = info2->argument;
		while (kek != NULL)
		{
			printf("argument %d = %s end\n", i, kek->argument);
			i++;
			kek = kek->next;
		}
		info2 = info2->next;		
	}
	free_all(info);
}