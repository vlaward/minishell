/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:51:15 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 15:55:50 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	int			n;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	n = 0;
	while (s1[n] != '\0')
		n++;
	if (n == 0)
	{
		ret = malloc(1);
		*ret = s1[n];
		return (ret);
	}
	n--;
	while (ft_strchr(set, s1[n]))
		n--;
	ret = malloc((n + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, (n + 2) * sizeof(char));
	return (ret);
}
