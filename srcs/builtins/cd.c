/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:43:07 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 11:34:13 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	oldpwd_updater(t_list *env, t_list *PWD)
{
	t_list	*oldpwd;
	char	*content;

	oldpwd = get_env_node(env, "OLDPWD");
	if (!oldpwd)
		return (perror("malloc"), 0);
	content = PWD->content + 3;
	content = ft_strjoin("OLDPWD", content);
	if (!content)
		return (perror("malloc"), 0);
	if (oldpwd->content)
		free(oldpwd->content);
	oldpwd->content = content;
	return (1);
}

static int	change_pwd(t_list *env)
{
	t_list	*pwd;
	char	content[PATH_MAX];
	char	*tmp;

	pwd = get_env_node(env, "PWD");
	if (!oldpwd_updater(env, pwd))
		return (-1);
	if (!getcwd(content, PATH_MAX))
		return (perror("getcwd"), errno);
	tmp = ft_strjoin("PWD=", content);
	if (!tmp)
		return (perror("malloc"), -1);
	free(pwd->content);
	pwd->content = tmp;
	return (0);
}

int	ft_cd(t_list **redirect, t_list *env, char **av)
{
	if (!av[1])
		return (free_args(av), ft_lstclear(redirect, free_cmd), ft_putestr_fd(
				"minishell: cd: too few arguments\n", STDERR_FILENO), 1);
	if (av[2])
		return (free_args(av), ft_lstclear(redirect, free_cmd), ft_putestr_fd(
				"minishell: cd: too many arguments\n", STDERR_FILENO), 1);
	if (chdir(av[1]) == -1)
		return (free_args(av), ft_lstclear(redirect, free_cmd)
			, perror("cd"), 1);
	return (free_args(av), ft_lstclear(redirect, free_cmd), change_pwd(env));
}
