/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:28:48 by ncrombez          #+#    #+#             */
/*   Updated: 2024/01/29 19:54:18 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstadd_back(t_list **lst, t_list *to_add)
{
	if (!lst || !to_add || *lst == NULL || to_add == *lst)
		return (0);
	to_add->next = *lst;
	*lst = to_add;
	return (1);
}
