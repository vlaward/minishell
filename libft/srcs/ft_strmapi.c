/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:55:11 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/10 17:14:07 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	n;
	char			*ret;

	n = 0;
	if (!s || !f)
		return (NULL);
	ret = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, ft_strlen(s) + 1);
	while (ret[n])
	{
		ret[n] = (*f)(n, ret[n]);
		n++;
	}
	return (ret);
}
