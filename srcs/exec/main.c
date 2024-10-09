/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:52:18 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 12:41:24 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	start(t_list **cmd, t_list *env);

static char	*cmd_redirects(t_list *cmd)
{
	char	*str;

	if (((t_cmd *)(cmd->content))->in
		&& dup2(((t_cmd *)(cmd->content))->in, STDIN_FILENO) == -1)
		return (perror("dup2 "), free_cmd(cmd), NULL);
	if (((t_cmd *)(cmd->content))->out
		&& dup2(((t_cmd *)(cmd->content))->out, STDOUT_FILENO) == -1)
		return (perror("dup2"), free_cmd(cmd), NULL);
	if (((t_cmd *)(cmd->content))->in)
		close(((t_cmd *)(cmd->content))->in);
	if (((t_cmd *)(cmd->content))->out)
		close(((t_cmd *)(cmd->content))->out);
	str = ((t_cmd *)(cmd->content))->cmd;
	free(cmd->content);
	free(cmd);
	return (str);
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
		return (printf("NIQUE BIEN TQ GRQND MERER SQLQLRLKWEQAEHQEAtr\n"), -1);
	if (pid)
	{
		dup2(pipette[0], STDIN_FILENO);
		(close(pipette[1]), close(pipette[0]));
		tmp = cmd->next;
		ft_lstdelone(cmd, free_cmd);
		return (start(&tmp, env));
	}
	ft_lstclear(&(cmd->next), free_cmd);
	dup2(pipette[1], STDOUT_FILENO);
	(close(pipette[1]), close(pipette[0]));
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

	if ((*cmd)->next)
		return (fork_thing(*cmd, env));
	if (!((t_cmd *)((*cmd)->content))->has_pipe)
		if (ft_builtins(((t_cmd *)((*cmd)->content))->cmd) != NULL)
			return (ft_builtins(((t_cmd *)((*cmd)->content))->cmd)(cmd, env
				, ft_minisplit(ft_strdup(((t_cmd *)((*cmd)->content))->cmd)
					, env)));
	if (errno == ENOMEM)
		return (ft_lstclear(cmd, free_cmd), -1);
	if (fork())
		return (ft_lstclear(cmd, free_cmd), go_back_to_main(env));
	close(TTY_SAVED_FD);
	splited_cmd = ft_minisplit(cmd_redirects(*cmd), env);
	exit(execute_cmd(splited_cmd, env));
}

static char	*read_prompt(t_list *env)
{
	static char	prompt[PATH_MAX];
	char		*pwd;
	int			i;

	pwd = ft_getenv("PWD", env);
	i = 0;
	while (*pwd && i < PATH_MAX - 3)
		prompt[i++] = *pwd++;
	ft_memcpy(&(prompt[i]), ">\0", 2);
	if (*pwd)
		ft_memcpy(&(prompt[PATH_MAX - 5]), "...>\0", 5);
	return (readline(prompt));
}

static int	handle_line(char *line, t_list *env)
{
	t_list	*cmd;
	int		exitcode;

	cmd = init_cmd(line, env);
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
	if (errno & (ENOMEM | EMFILE | ENFILE | ENOSPC))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*new_env;

	((void)ac, (void)av);
	new_env = init_env(env);
	line = NULL;
	dup(STDIN_FILENO);
	while (1)
	{
		errno = 0;
		if (!gere_sig(READING_LINE))
			return (0);
		line = read_prompt(new_env);
		if (!line)
			break ;
		line = tatu_ferme_tes_guillemets(line);
		if ((line && !handle_line(line, new_env)) || (!line
				&& (errno & (EINVAL | ENOMEM))))
			break ;
		rl_on_new_line();
	}
	close(TTY_SAVED_FD);
	ft_lstclear(&new_env, free);
	rl_clear_history();
	return (0);
}
