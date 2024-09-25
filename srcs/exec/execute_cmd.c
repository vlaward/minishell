/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:36:05 by ncrombez          #+#    #+#             */
/*   Updated: 2024/09/25 19:57:49 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitest.h"
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
	if (ft_putestr_fd("minishell: ", STDERR_FILENO) == -1)
		(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
	if (flag == ACCESS_F)
		if (ft_putestr_fd(strerror(errno), STDERR_FILENO) == -1)
			(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
	if (flag != ACCESS_F)
		if (ft_putestr_fd("command not found", STDERR_FILENO) == -1)
			(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
	if (ft_putestr_fd(": ", STDERR_FILENO) == -1)
		(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
	if (ft_putestr_fd(file, STDERR_FILENO) == -1)
		(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
	if (ft_putechar_fd('\n', STDERR_FILENO) == -1)
		(ft_putechar_fd('\n', STDERR_FILENO), perror("write"));
}

static void	launch_executable(char **args, char **tabl_env, char **paths)
{
	int		i;
	char	*tmp;

	if (*(args[0]) == '.' || !ft_strncmp(args[0], "/", 1))
	{
		if (access(args[0], F_OK) == -1 || access(args[0], X_OK) == -1)
			return (free_args(paths), access_error(args[0], ACCESS_F));
		execve(args[0], args, tabl_env);
		return ;
	}
	if (!paths)
		return (free_args(paths), access_error(args[0], 0));
	tmp = ft_strjoin("/", args[0]);
	if (!tmp)
		return (free_args(paths), free(paths));
	i = 0;
	while (paths[i] != NULL)
	{
		free(args[0]);
		args[0] = ft_strjoin(paths[i++], tmp);
		if (!access(args[0], F_OK) && access(args[0], X_OK) == -1)
			return (free(tmp), free_args(paths), access_error(*args, 1));
		execve(args[0], args, tabl_env);
	}
	return (free_args(paths), free(tmp), access_error(args[0], 0));
}

int	execute_cmd(char **args, t_list *env)
{
	char	**tabl_env;

	if (!args || *args == NULL)
		exit(errno);
	if (ft_builtins(args[0]))
		exit(ft_builtins(args[0])(NULL, env, args));
	close(TTY_SAVED_FD);
	tabl_env = env_to_tabl(env);
	if (!tabl_env)
		(perror("malloc"), exit(errno));
	launch_executable(args, tabl_env,
		ft_split(ft_getenv("PATH", env), ':'));
	free_args(args);
	free(tabl_env);
	ft_lstclear(&env, free);
	if (!errno)
		exit(127);
	exit(errno);
}
