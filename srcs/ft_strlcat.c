/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:19 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 14:50:10 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	long unsigned int	i;
	long unsigned int	j;
	long unsigned int	ret;

	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	i = (size_t)ft_strlen(dst);
	ret = i;
	j = 0;
	if (size < i || size == 0)
		return (size + ft_strlen(src));
	if (!dst && size == 0)
		return (ft_strlen(src));
	while (i < size -1 && src[j])
		dst[i++] = src[j++];
	if (i < size)
		dst[i] = '\0';
	return (ret + ft_strlen(src));
}
