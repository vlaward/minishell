/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:15:38 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 14:58:47 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libft.h"

int	ft_len(const char *s)
{
	const char	*d;

	d = s;
	while (*d)
		d++;
	return (d - s);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	if (str == NULL && to_find == NULL)
		return (NULL);
	if (to_find[i] == 0)
		return ((char *)str);
	if (str == NULL && len == 0)
		return (NULL);
	while (str[i] != '\0' && len > 0)
	{
		o = 0;
		while (str[i + o] == to_find[o] && str[i + o] && to_find[o]
			&& len-- > 0)
			o++;
		if (o == ft_len(to_find))
			return ((char *)&str[i]);
		i++;
		len += o -1;
	}
	return (NULL);
}
