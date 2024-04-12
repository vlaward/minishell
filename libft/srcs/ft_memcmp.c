/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:12:55 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/09 15:33:26 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*d;
	unsigned char	*t;

	d = (unsigned char *)s1;
	t = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (d[i] == t[i] && i < n - 1)
	i++;
	return (d[i] - t[i]);
}
