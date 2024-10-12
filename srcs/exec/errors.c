/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:53:06 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/12 13:07:03 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline int	big_error(void)
{
	return (errno == ENOMEM || errno == EMFILE
		|| errno == ENFILE || errno == ENOSPC);
}

void	export_error(char *str, int i)
{
	if (i == -1)
	{
		ft_putestr_fd("export: \'", STDERR_FILENO);
		ft_putestr_fd(str, STDERR_FILENO);
		ft_putestr_fd("\': not a valid identifier\n", STDERR_FILENO);
	}
}

void	syntax_error(char *str)
{
	ft_putestr_fd("minishell: syntax errror near unexpected tokken \'",
		STDERR_FILENO);
	if (str)
		ft_putechar_fd(*str, STDERR_FILENO);
	else
		ft_putestr_fd("newline", STDERR_FILENO);
	ft_putestr_fd("\'\n", STDERR_FILENO);
}

void	guille_error(void)
{
	ft_putestr_fd("unexpected EOF while lookink for matching", STDERR_FILENO);
	ft_putestr_fd(" `\"\'\nsyntax error unexpected end of file\n", STDERR_FILENO);
}

void	execve_error(char *file)
{
	if (ft_putestr_fd("minishell: ", STDERR_FILENO) == -1
		|| ft_putestr_fd(file, STDERR_FILENO) == -1
		|| ft_putestr_fd(": ", STDERR_FILENO) == -1)
		perror("write");
	perror(NULL);
}
