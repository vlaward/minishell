/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:45:51 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 13:49:44 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*t;

	if (!lst)
		return (NULL);
	ret = ft_lstnew((*f)(lst->content));
	if (!ret)
		return (NULL);
	t = ret;
	while (lst->next != NULL)
	{
		lst = lst->next;
		t->next = ft_lstnew((*f)(lst->content));
		if (!t->next)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		t = t->next;
	}
	return (ret);
}
