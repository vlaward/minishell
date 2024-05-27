/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:27:47 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 14:56:09 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*s2;
	int		i;

	if (size <= 0 || !s)
		return (NULL);
	if (size <= ft_strlen(s))
		s2 = malloc(sizeof(char) * (size + 1));
	else
		s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && size-- > 0)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
