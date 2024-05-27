/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:39:26 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/10 16:12:38 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;

	d = dest;
	if (dest != src)
	{
		if (dest > src)
		{
			dest += n -1;
			src += n - 1;
			while (n > 0)
			{
				*(char *)dest-- = *(char *)src--;
				n--;
			}
		}
		else
			while (n-- > 0)
				*(char *)dest++ = *(char *)src++;
	}
	dest = d;
	return (dest);
}
