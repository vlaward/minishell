/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:55:06 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/09 15:33:04 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*d;

	d = (char *)s;
	while (*d && *d != (const char)c)
		d++;
	if (*d == '\0' && (const char)c != '\0')
		return (NULL);
	return (d);
}
