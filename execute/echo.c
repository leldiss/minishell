/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:21:51 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 20:05:50 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	second_output(t_execute *cmds, int len)
{
	int	i;

	i = 0;
	if (cmds->option)
		printf("%s ", cmds->option);
	while (++i < len - 1)
		printf("%s ", cmds->arguments[i]);
	if (cmds->arguments[i])
		printf("%s", cmds->arguments[i]);
	printf("\n");
}

static void	first_output(t_execute *cmds, int len)
{
	int	i;

	i = 0;
	while (++i < len - 1)
		printf("%s ", cmds->arguments[i]);
	if (cmds->arguments[i])
		printf("%s", cmds->arguments[i]);
}

int	echo(t_execute *cmds, t_info *info)
{
	int	len;
	int	flag;

	flag = 0;
	len = ft_arg_len(cmds->arguments);
	if (cmds->option)
	{
		if (cmds->option[0] == '-' && cmds->option[1]
			== 'n' && cmds->option[2] == 0)
			flag = 1;
	}
	if (flag == 1)
		first_output(cmds, len);
	if (flag == 0)
		second_output(cmds, len);
	info->status = 0;
	return (0);
}
