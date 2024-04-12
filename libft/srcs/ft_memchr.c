/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:57:00 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/11 19:07:08 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*d;

	d = (const char *)s;
	if (n == 0)
		return (NULL);
	n--;
	while (n > 0 && *d != (char)c)
	{
		n--;
		d++;
	}
	if (*d == (char)c)
		return ((void *)d);
	return (NULL);
}
