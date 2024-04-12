/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:32:10 by ncrombez          #+#    #+#             */
/*   Updated: 2024/02/06 17:20:14 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*p2(char *ret, long dyxit, int a, char *charset)
{
	int		i;
	long	n;

	i = 0;
	n = (long)a;
	if (a < 0)
	{
		ret[i] = '-';
		i++;
		a += 1;
		n = -n;
	}
	while (dyxit >= (long)ft_strlen(charset))
	{
		ret[i++] = charset[n / dyxit];
		n = n % dyxit;
		dyxit /= ft_strlen(charset);
	}
	ret[i] = charset[n / dyxit];
	i++;
	ret[i] = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	long	dyxit;
	int		alloc;
	char	*ret;

	dyxit = 1;
	alloc = 2;
	while (n >= dyxit * 10 || n <= -(dyxit * 10))
	{
		dyxit = dyxit * 10;
		alloc++;
		if (dyxit == 1000000000)
			break ;
	}
	if (n < 0)
		alloc ++;
	ret = malloc(alloc * sizeof(char));
	if (!ret)
		return (NULL);
	ret = p2(ret, dyxit, n, "0123456789");
	return (ret);
}

//on peu rajouter le charset check de printf
char	*ft_itoa_base(int n, char *charset)
{
	long	dyxit;
	int		alloc;
	int		size;
	char	*ret;

	if (!charset)
		return (NULL);
	size = ft_strlen(charset);
	dyxit = 1;
	alloc = 2;
	while (n >= dyxit * size || n <= -(dyxit * size))
	{
		dyxit = dyxit * size;
		alloc++;
		if (dyxit == 1000000000)
			break ;
	}
	if (n < 0)
		alloc ++;
	ret = malloc(alloc * sizeof(char));
	if (!ret)
		return (NULL);
	ret = p2(ret, dyxit, n, charset);
	return (ret);
}
