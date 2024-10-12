/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:36:05 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/12 16:15:17 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define ACCESS_F 1

static char	**env_to_tabl(t_list *env)
{
	char	**ret;
	char	**tmp;

	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (env)
	{
		*(tmp++) = (char *)(env->content);
		env = env->next;
	}
	*tmp = NULL;
	return (ret);
}

static void	access_error(char *file, int flag)
{
	if (ft_putestr_fd("minishell: ", STDERR_FILENO) == -1
		|| ft_putestr_fd(file, STDERR_FILENO) == -1
		|| ft_putestr_fd(": ", STDERR_FILENO) == -1)
		perror("write");
	if (flag == ACCESS_F)
		if (ft_putestr_fd(strerror(errno), STDERR_FILENO) == -1)
			perror("write");
	if (flag != ACCESS_F)
		if (ft_putestr_fd("command not found", STDERR_FILENO) == -1)
			perror("write");
	if (ft_putechar_fd('\n', STDERR_FILENO) == -1)
		perror("write");
}

static int	launch_executable(char **args, char **tabl_env, char **paths)
{
	int		i;
	char	*tmp;

	if (*(args[0]) == '.' || *(args[0]) == '/')
		if (access(args[0], F_OK) == -1)
			return (free_args(paths), access_error(args[0], ACCESS_F), 1);
	if (*(args[0]) == '.' || *(args[0]) == '/')
		if (execve(args[0], args, tabl_env) == -1)
			return (free_args(paths), execve_error(args[0]), 0);
	if (!paths)
		return (free_args(paths), access_error(args[0], 0), errno - 126);
	tmp = ft_strjoin("/", args[0]);
	if (!tmp)
		return (free_args(paths), free(paths), errno - 126);
	i = 0;
	while (paths[i] != NULL)
	{
		free(args[0]);
		args[0] = ft_strjoin(paths[i++], tmp);
		if (!args[0])
			return (free(tmp), free_args(paths), errno - 126);
		if (!access(args[0], F_OK) && execve(args[0], args, tabl_env))
			return (free(tmp), free_args(paths), execve_error(args[0]), 0);
	}
	return (free_args(paths), free(tmp), access_error(args[0], 0), 1);
}

int	execute_cmd(char **args, t_list *env)
{
	char	**tabl_env;
	int		ret;

	ret = 0;
	close(TTY_SAVED_FD);
	if (args && *args != NULL && !ft_builtins(args[0]))
	{
		tabl_env = env_to_tabl(env);
		if (tabl_env)
		{
			ret = 126 + launch_executable(args, tabl_env,
					ft_split(ft_getenv("PATH", env), ':'));
			(free(tabl_env), free_args(args));
			ft_lstclear(&env, free);
			exit(ret);
		}
		(perror("malloc"), free_args(args));
	}
	else if (args && *args != NULL)
		ret = ft_builtins(args[0])(NULL, env, args);
	ft_lstclear(&env, free);
	if (errno)
		exit(errno);
	exit(ret);
}
