/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:44:23 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/23 15:16:35 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putenbr_fd(int nb, int fd)
{
	long	dyxe;
	long	temp;
	long	ret;
	long	nbr;

	dyxe = 1;
	nbr = (long)nb;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	while (nbr >= dyxe * 10)
	{
		dyxe = dyxe * 10;
	}
	while (dyxe >= 1)
	{
		ret = nbr % dyxe;
		temp = (nbr - ret) / dyxe + '0';
		write (fd, &temp, 1);
		nbr = ret;
		dyxe = dyxe / 10;
	}
}
