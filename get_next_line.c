/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:15:36 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/22 12:33:30 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lelen(char *str, int arg, int place)
{
	int	i;

	i = 0;
	if (arg == 1)
	{
		while (str[place + i] != '\0')
			i++;
	}
	else if (arg == 2)
	{
		while (str[place + i] != '\0' && str[place + i] != '\n')
			i++;
		if (str[place + i] == '\n')
			i++;
	}
	return (i);
}

char	*putret(char buff[], char *ret, int fd, int *p)
{
	char	*ret2;
	int		o;
	int		i;

	o = 0;
	i = 0;
	while (i < BUFFER_SIZE)
			buff[i++] = '\0';
	i = 0;
	read(fd, buff, BUFFER_SIZE);
	ret2 = malloc(lelen(ret, 1, 0) + lelen(buff, 2, 0) + 1);
	if (!ret)
		return (NULL);
	while (ret[o] != '\0')
	{
		ret2[o] = ret[o];
		o++;
	}
	while (i < BUFFER_SIZE && buff[i] != '\0' && buff[i] != '\n')
		ret2[o++] = buff[i++];
	free(ret);
	ret2[o] = '\0';
	*p = i;
	return (ret2);
}

char	*p2(char *buff, char *ret, int fd, int *d)
{
	int	i;
	int	cont;

	i = *d;
	cont = 0;
	while (i < BUFFER_SIZE && buff[i] != '\0' && buff[i] != '\n')
		ret[cont++] = buff[i++];
	ret[cont] = '\0';
	while ((i != BUFFER_SIZE && (buff[i] != '\n' && buff[i] != '\0'))
		|| (i == BUFFER_SIZE && (buff[i - 1] != '\n' && buff[i - 1] != '\0')))
	{
		ret = putret(buff, ret, fd, &i);
		if (!ret)
			return (NULL);
		cont = lelen(ret, 1, 0);
	}
	if (buff[i] == '\n')
		ret[cont++] = '\n';
	ret[cont] = '\0';
	i += 1;
	*d = i;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*ret;
	static int	i;

	if (buff[0] == '\0' || i == BUFFER_SIZE)
	{
		i = 0;
		while (i <= BUFFER_SIZE)
			buff[i++] = '\0';
		i = 0;
		read(fd, buff, BUFFER_SIZE);
	}
	if (buff[i] == '\0')
		return (NULL);
	ret = malloc(lelen(buff, 2, i) + 1);
	if (!ret)
		return (NULL);
	return (p2(buff, ret, fd, &i));
}
