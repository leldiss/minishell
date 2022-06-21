/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 20:48:30 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_first(t_info *info, char *key)
{
	t_list	*tmp;
	t_list	*head;

	key = key;
	tmp = info->l_envp;
	info->l_envp = info->l_envp->next;
	head = info->l_envp;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	while (info->l_envp->next)
	{
		info->l_envp->head = head;
		info->l_envp = info->l_envp->next;
	}
	info->l_envp->head = head;
	info->l_envp = info->l_envp->head;
	return (1);
}

static void	check_list(t_info *info, char *key)
{
	t_list	*tmp;

	if (string_compare(info->l_envp->key, key))
		check_first(info, key);
	else
	{
		while (info->l_envp->next)
		{
			if (info->l_envp->next->key)
			{
				if (string_compare(info->l_envp->next->key, key))
				{
					tmp = info->l_envp->next;
					if (info->l_envp->next->next)
						info->l_envp->next = info->l_envp->next->next;
					else
						info->l_envp->next = NULL;
					free(tmp->key);
					free(tmp->value);
					free(tmp);
				}
			}
			info->l_envp = info->l_envp->next;
		}
	}
}

int	unset(t_execute *cmds, t_info *info)
{
	int		i;

	i = 0;
	while (cmds->arguments[++i])
	{
		if (!cmds->arguments[i])
			continue ;
		if (cmds->arguments[i][0] == 0)
			continue ;
		info->l_envp = info->l_envp->head;
		check_list(info, cmds->arguments[i]);
		info->l_envp = info->l_envp->head;
	}
	return (0);
}
