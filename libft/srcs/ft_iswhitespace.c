/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 06:49:51 by ncrombez          #+#    #+#             */
/*   Updated: 2024/06/20 07:07:37 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_iswhitespace(char c)
{
	if (!c)
		return (0);
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}