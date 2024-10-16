/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:45:53 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/12 14:32:51 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_list **redirect, t_list *env, char **cmd)
{
	int		bkslsh_n;
	char	**tmp;
	int		isout;

	isout = STDOUT_FILENO;
	if (redirect && ((t_cmd *)((*redirect)->content))->out)
		isout = ((t_cmd *)((*redirect)->content))->out;
	tmp = cmd;
	bkslsh_n = 1;
	while (++cmd && !ft_strcmp(*cmd, "-n"))
		bkslsh_n = 0;
	while (*cmd)
	{
		if (ft_putestr_fd(*(cmd++), isout) == -1)
			return (ft_lstclear(redirect, free_cmd)
				, perror("write"), free_args(tmp), 1);
		if (*cmd)
			if (ft_putechar_fd(' ', isout) == -1)
				return (ft_lstclear(redirect, free_cmd)
					, perror("write"), free_args(tmp), 1);
	}
	if (ft_putechar_fd('\n' * bkslsh_n, isout) == -1)
		return (ft_lstclear(redirect, free_cmd)
			, perror("write"), free_args(tmp), 1);
	return (free_args(tmp), (void)env, ft_lstclear(redirect, free_cmd), 0);
}
