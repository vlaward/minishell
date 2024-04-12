/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:06:25 by ncrombez          #+#    #+#             */
/*   Updated: 2023/12/14 16:40:44 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;

	if (size && nmemb > ((sizeof(char) * 2147483424) / size))
		return (NULL);
	s = malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_memset(s, '\0', nmemb * size);
	if (!s)
		return (NULL);
	return (s);
}
