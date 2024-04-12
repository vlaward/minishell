/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:40:59 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 14:48:57 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;

	d = (char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*(char *)dest++ = *(const char *)src++;
		n--;
	}
	dest = d;
	return (dest);
}
