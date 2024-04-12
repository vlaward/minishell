/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:21 by ncrombez          #+#    #+#             */
/*   Updated: 2023/12/19 17:42:43 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char	*nptr)
{
	int	retour;
	int	signe;

	retour = 0;
	signe = 1;
	if (*nptr == '\0')
		return (0);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			signe = -1;
	while (nptr[1] != '\0' && *nptr >= '0' && *nptr <= '9')
	{
		retour = 10 * retour + (*nptr - 48);
		nptr++;
	}
	if (*nptr < '0' || *nptr > '9')
		return (retour * signe);
	return ((10 * retour + (*nptr - 48)) * signe);
}

int	ft_atoi_base(char *nptr, char *charset)
{
	int	retour;
	int	signe;
	int	i;

	retour = 0;
	signe = 1;
	if (*nptr == '\0')
		return (0);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			signe = -1;
	while (*nptr != '\0')
	{
		i = 0;
		while (charset[i] != *nptr && charset[i] != '\0')
			i++;
		if (charset[i] == '\0')
			return (0);
		retour = ft_strlen(charset) * retour + i;
		nptr++;
	}
	return (retour * signe);
}
