/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:46:08 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/05 06:51:15 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitest.h"

int	ft_unset(t_list **redirect, t_list *env, char **av)
{
	int		i;
	t_list	*tmp;
	t_list	*incr;

	if (!av[1])
		return (0);
	i = 0;
	while (av[++i])
	{
		incr = env;
		while (incr->next != NULL && ft_strncmp(av[i]
				, incr->next->content, ft_strlen(av[i])))
			incr = incr->next;
		if (incr->next)
		{
			tmp = incr->next;
			incr->next = tmp->next;
			ft_lstdelone(tmp, free);
		}
	}
	free_args(av);
	return (ft_lstclear(redirect, free_cmd), 1);
}
