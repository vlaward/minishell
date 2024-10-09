/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:53:06 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/09 13:04:50 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline int	big_error(void)
{
	return (errno == ENOMEM || errno == EMFILE
		|| errno == ENFILE || errno == ENOSPC);
}
