/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:31:56 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 14:59:50 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	const char			*s2;
	char				*ret;
	long unsigned int	n;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		s2 = s + ft_strlen(s);
	else
		s2 = s + start;
	n = 0;
	if (ft_strlen(s2) < len)
		ret = ft_calloc(ft_strlen(s2) + 1, sizeof(char));
	else
		ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (n < len && s2[n] != '\0')
	{
		ret[n] = s2[n];
		n++;
	}
	ret[n] = '\0';
	return (ret);
}
