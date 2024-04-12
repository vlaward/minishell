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

int	ft_isin_table(int value, int *table, int size)
{
	int	i;

	i = 0;
	if (!table)
		return (0);
	while (i < size && table[i])
		if (value == table[i++])
			return (1);
	return (0);
}
