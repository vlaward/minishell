/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:36 by ncrombez          #+#    #+#             */
/*   Updated: 2024/02/06 17:13:52 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft.h"

int	ft_isin_table(int value, char *table)
{
	char	*tmp;
	
	if (!table)
		return (-1);
	tmp = table;
	while (*tmp != '\0')
		if (value == *tmp++)
			return (1);
	return (0);
}
