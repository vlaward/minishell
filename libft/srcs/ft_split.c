/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:06:20 by ncrombez          #+#    #+#             */
/*   Updated: 2024/07/15 11:55:43 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static int	ft_splitlen(const char *s, char c)
{
	int	n;

	n = 0;
	if (s == NULL)
		return (0);
	while (s[n] != c && s[n] != '\0')
		n++;
	return (n + 1);
}

static int	ft_fullsplitlen(const char *s, char c)
{
	int	n;
	int	o;

	n = 0;
	o = 0;
	if (s == NULL)
		return (0);
	if (*s != c && *s != '\0')
		n++;
	while (s[o] != '\0')
	{
		if (s[o] == c && s[o + 1] != c && s[o + 1] != '\0')
			n++;
		o++;
	}
	return (n + 1);
}

static const char	*putin(const char	*s, char c, int n, char **ret)
{
	int	o;

	o = 0;
	ret[n] = (char *)malloc(ft_splitlen(s, c) * sizeof(char));
	if (!ret[n])
		return (NULL);
	while (*s != c && *s != '\0')
		ret[n][o++] = *s++;
	ret[n][o] = '\0';
	return (s);
}

static void	*fullsup(char **ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	while (i > 0)
	{
		free(ret[i]);
		i--;
	}
	free(*ret);
	free(ret);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		n;

	if (s == NULL || *s == '\0')
		return (NULL);
	ret = (char **)malloc(ft_fullsplitlen(s, c) * sizeof(char *));
	if (!ret)
		return (NULL);
	n = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			s = putin(s, c, n, ret);
			if (s == NULL)
				return (fullsup(ret));
			n++;
		}
	}
	ret[n] = NULL;
	return (ret);
}
