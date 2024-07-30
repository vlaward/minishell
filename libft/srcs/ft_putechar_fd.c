/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putechar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:36:28 by ncrombez          #+#    #+#             */
/*   Updated: 2024/07/29 19:18:47 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"

int	ft_putechar(int ch) {
	return write(1, &ch, 1);
}

int	ft_putechar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
