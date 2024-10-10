/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:45:56 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/10 14:37:00 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dowe_write_node(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*str++ == '=')
			return (1);
	return (0);
}

int	ft_env(t_list **redirect, t_list *env, char **cmd)
{
	int	isout;

	isout = STDOUT_FILENO;
	if (redirect)
		isout = ((t_cmd *)((*redirect)->content))->out;
	while (env)
	{
		if (dowe_write_node(env->content))
		{
			if (ft_putestr_fd(env->content, isout) == -1)
				return (ft_lstclear(redirect, free_cmd)
					, perror("write"), free_args(cmd), errno);
			if (ft_putechar_fd('\n', isout) == -1)
				return (ft_lstclear(redirect, free_cmd)
					, perror("write"), free_args(cmd), errno);
		}
		env = env->next;
	}
	free_args(cmd);
	return (ft_lstclear(redirect, free_cmd), 1);
}
//VERIFIER L'UTILISATION DE WRITE
