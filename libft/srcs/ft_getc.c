/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 07:40:57 by ncrombez          #+#    #+#             */
/*   Updated: 2024/06/12 07:41:07 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_getc(FILE *file)
{
	int	ret;

	if (!read(file->_fileno, &ret, 1))
		return (EOF);
	return (ret);
}
