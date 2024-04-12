/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:40:51 by ncrombez          #+#    #+#             */
/*   Updated: 2024/02/06 17:17:13 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*t;

	if (lst == NULL || f == NULL)
		return (0);
	t = lst;
	while (t->next != NULL)
	{
		(*f)(t->content);
		t = t->next;
	}
	(*f)(t->content);
	return (1);
}
