/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:52:18 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/12 16:12:14 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_qm(int i, t_list *env)
{
	free(env->content);
	env->content = ft_itoa(i);
	if (!env->content)
		return (perror("malloc"), 0);
	return (1);
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

int	main_loop(char *line, t_list *env)
{
	errno = 0;
	g_sig_catcher = 0;
	if (!gere_sig(READING_LINE))
		return (0);
	line = read_prompt(env);
	if (g_sig_catcher != 0)
		if (!change_qm(g_sig_catcher, env))
			return (0);
	if (!line)
		return (0);
	if (started_by_pipe(line))
	{
		free(line);
		line = NULL;
		if (!change_qm(g_sig_catcher, env))
			return (0);
	}
	line = tatu_ferme_tes_guillemets(line, env);
	if ((line && !handle_line(line, env)) || (!line
			&& big_error()))
		return (0);
	rl_on_new_line();
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*new_env;

	((void)ac, (void)av);
	if (dup(STDIN_FILENO) == -1 || !gere_sig(QUITE_CORE))
		return (errno);
	new_env = init_env(env);
	line = NULL;
	while (1)
		if (!main_loop(line, new_env))
			break ;
	(close(TTY_SAVED_FD), ft_lstclear(&new_env, free), rl_clear_history());
	return (errno);
}
