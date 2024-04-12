/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:25:40 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 16:15:49 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*t;

	i = 1;
	t = lst;
	if (lst == NULL)
		return (0);
	while (t->next != NULL)
	{
		t = t->next;
		i++;
	}
	return (i);
}
