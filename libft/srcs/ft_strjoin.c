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

	n = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ret = malloc(n * sizeof(char));
	if (!ret)
		return (NULL);
	n = 0;
	while (s1 != NULL && *s1 != '\0')
		ret[n++] = *s1++;
	while (s2 != NULL && *s2 != '\0')
		ret[n++] = *s2++;
	ret[n] = '\0';
	if (n == 0)
		return (free(ret), NULL);
	return (ret);
}

char	*ft_strjoin_n_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	(free(s1), free(s2));
	return (ret);
}