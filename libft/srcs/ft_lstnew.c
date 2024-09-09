/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:21 by ncrombez          #+#    #+#             */
/*   Updated: 2024/09/09 13:30:36 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*t;

	t = malloc (sizeof(void *) + sizeof(t_list *));
	if (!t)
		return (NULL);
	t->content = content;
	t->next = NULL;
	return (t);
}

t_list	*ft_lstnew_content_mandatory(void *content)
{
	t_list	*t;

	if (!content)
		return (NULL);
	t = malloc (sizeof(void *) + sizeof(t_list *));
	if (!t)
		return (NULL);
	t->content = content;
	t->next = NULL;
	return (t);
}