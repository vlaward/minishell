/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:22:52 by ncrombez          #+#    #+#             */
/*   Updated: 2024/01/29 19:43:02 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*t;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = *lst;
		while (t->next != NULL)
			t = t->next;
		t->next = new;
	}
	if (new->next == new)
		new->next = NULL;
	return (1);
}
