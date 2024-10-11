/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:00:02 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/11 18:19:40 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	start(t_list **cmd, t_list *env);

int	is_empty(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	return (*str == '\0');
}

static int	fork_thing(t_list *cmd, t_list *env)
{
	int		pid;
	int		pipette[2];
	t_list	*tmp;
	char	**splited_cmd;

	pipe(pipette);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid)
	{
		if (dup2(pipette[0], STDIN_FILENO) == -1
			|| close(pipette[1]) == -1 || close(pipette[0]) == -1)
			(ft_lstclear(&cmd, free_cmd), ft_lstclear(&env, free), exit(errno));
		tmp = cmd->next;
		ft_lstdelone(cmd, free_cmd);
		return (start(&tmp, env));
	}
	ft_lstclear(&(cmd->next), free_cmd);
	dup2(pipette[1], STDOUT_FILENO);
	(close(pipette[1]), close(pipette[0]));
	if (is_empty(((t_cmd *)((cmd)->content))->cmd))
		(ft_lstclear(&cmd, free_cmd), ft_lstclear(&env, free), exit(1));
	splited_cmd = ft_minisplit(cmd_redirects(cmd), env);
	exit(execute_cmd(splited_cmd, env));
}

static int	go_back_to_main(t_list *env)
{
	int	status;

	status = 0;
	close(STDIN_FILENO);
	dup(TTY_SAVED_FD);
	if (!gere_sig(0))
		return (-1);
	while (wait(&status) != -1)
	{
		if (WEXITSTATUS(status) != ft_atoi(env->content))
		{
			free(env->content);
			env->content = ft_itoa(WEXITSTATUS(status));
			if (!env->content)
				return (perror("malloc"), -1);
		}
	}
	return (WEXITSTATUS(status));
}

static int	start(t_list **cmd, t_list *env)
{
	char	**splited_cmd;

	if (big_error())
		return (ft_lstclear(cmd, free_cmd), -1);
	if ((*cmd)->next)
		return (fork_thing(*cmd, env));
	if (!((t_cmd *)((*cmd)->content))->has_pipe)
		if (ft_builtins(((t_cmd *)((*cmd)->content))->cmd) != NULL)
			return (ft_builtins(((t_cmd *)((*cmd)->content))->cmd)(cmd, env
				, ft_minisplit(ft_strdup(((t_cmd *)((*cmd)->content))->cmd)
					, env)));
	if (big_error() && ((t_cmd *)((*cmd)->content))->has_pipe)
		(ft_lstclear(cmd, free_cmd), ft_lstclear(&env, free), exit(errno));
	if (big_error())
		return (ft_lstclear(cmd, free_cmd), -1);
	if (fork())
		return (ft_lstclear(cmd, free_cmd), go_back_to_main(env));
	if (is_empty(((t_cmd *)((*cmd)->content))->cmd))
		(ft_lstclear(cmd, free_cmd), ft_lstclear(&env, free), exit(1));
	close(TTY_SAVED_FD);
	splited_cmd = ft_minisplit(cmd_redirects(*cmd), env);
	exit(execute_cmd(splited_cmd, env));
}

int	handle_line(char *line, t_list *env)
{
	t_list	*cmd;
	int		exitcode;

	cmd = init_cmd(line, env);
	if (big_error())
		return (0);
	if (cmd)
	{
		exitcode = start(&cmd, env);
		if (exitcode == -1)
			return (0);
		if (exitcode != ft_atoi(env->content))
		{
			free(env->content);
			env->content = ft_itoa(exitcode);
			if (!env->content)
				return (perror("malloc"), 0);
		}
	}
	return (1);
}
