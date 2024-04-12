/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:58:05 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/15 12:37:57 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*d;

	d = NULL;
	while (*s)
	{
		if (*s == (const char)c)
			d = (char *)s;
		s++;
	}
	if (*s == (const char)c)
		return ((char *)s);
	return (d);
}
