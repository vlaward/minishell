/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putechar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:36:28 by ncrombez          #+#    #+#             */
/*   Updated: 2023/05/23 15:16:35 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"

int	ft_putechar(int ch) {
	return write(1, &ch, 1);
}
void	ft_putechar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
