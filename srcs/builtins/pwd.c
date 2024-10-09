/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:46:04 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/09 11:34:13 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define PWDK_L 4

//une fois cd fait a changer ?
int	ft_pwd(t_list **redirect, t_list *env, char **cmd)
{
	int		isout;

	isout = STDOUT_FILENO;
	if (redirect)
		isout = ((t_cmd *)((*redirect)->content))->out;
	if (ft_putestr_fd(ft_getenv("PWD", env), isout) == -1)
		return (ft_lstclear(redirect, free_cmd), free_args(cmd)
			, perror("write"), 0);
	if (ft_putechar_fd('\n', isout) == -1)
		return (ft_lstclear(redirect, free_cmd), free_args(cmd)
			, perror("write"), 0);
	free_args(cmd);
	return (ft_lstclear(redirect, free_cmd), 1);
}
