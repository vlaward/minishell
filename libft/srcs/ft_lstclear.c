/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:16:03 by ncrombez          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:17 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*s;

	if (lst == NULL || *lst == NULL)
		return ;
	t = *lst;
	while (t->next != NULL)
	{
		s = t->next;
		ft_lstdelone(t, del);
		t = s;
	}
	ft_lstdelone(t, del);
	*lst = NULL;
}
