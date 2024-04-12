/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:44:34 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 15:55:33 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		n;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	n = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ret = malloc(n * sizeof(char));
	if (!ret)
		return (NULL);
	n = 0;
	while (*s1 != '\0')
		ret[n++] = *s1++;
	while (*s2 != '\0')
		ret[n++] = *s2++;
	ret[n] = '\0';
	return (ret);
}
