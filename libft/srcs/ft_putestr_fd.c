/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putestr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:39:07 by ncrombez          #+#    #+#             */
/*   Updated: 2024/07/29 19:22:10 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int	ft_putestr_fd(char *s, int fd)
{
	if (s != NULL)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}
