/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:13:38 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/16 16:01:53 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	n;

	if (s == NULL || f == NULL)
		return ;
	n = 0;
	while (s[n] != '\0')
	{
		(*f)(n, &s[n]);
		n++;
	}
}
