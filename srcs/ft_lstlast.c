/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:15:35 by ncrombez          #+#    #+#             */
/*   Updated: 2023/10/18 14:48:43 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*t;

	if (!lst)
		return (NULL);
	t = lst;
	while (t->next != NULL)
		t = t->next;
	return (t);
}

//this fuction return not the last node, but the one  prior, of a list.
t_list	*ft_lstblast(t_list *lst)
{
	t_list	*t;
	t_list	*bt;

	if (!lst)
		return (NULL);
	bt = NULL;
	t = lst;
	while (t->next != NULL)
	{
		bt = t;
		t = t->next;
	}
	return (bt);
}
