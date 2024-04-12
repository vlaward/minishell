/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:55:13 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/09 16:30:53 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*d;

	d = (char *)s;
	while (n > 0)
	{
		*d = c;
		n--;
		d++;
	}
	return (s);
}
