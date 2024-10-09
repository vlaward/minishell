/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:45:37 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/05 06:45:37 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(char **args)
{
	char	**tmp;

	tmp = args;
	while (*tmp)
		free(*(tmp++));
	free(args);
}

int	builtin_cmp(const char *str, const char *builtin)
{
	char	tmp;

	if (ft_strncmp(str, builtin, ft_strlen(builtin)))
		return (0);
	tmp = *(str + ft_strlen(builtin));
	if (ft_iswhitespace(tmp) || !tmp)
		return (1);
	return (0);
}

t_builtin	ft_builtins(char *str)
{
	if (!str)
		return (NULL);
	while (ft_iswhitespace(*str))
		str++;
	if (builtin_cmp(str, "echo"))
		return (ft_echo);
	if (builtin_cmp(str, "env"))
		return (ft_env);
	if (builtin_cmp(str, "unset"))
		return (ft_unset);
	if (builtin_cmp(str, "export"))
		return (ft_export);
	if (builtin_cmp(str, "pwd"))
		return (ft_pwd);
	if (builtin_cmp(str, "cd"))
		return (ft_cd);
	if (builtin_cmp(str, "exit"))
		return (ft_exit);
	return (NULL);
}
