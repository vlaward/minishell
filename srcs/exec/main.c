/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:52:18 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/10 16:06:39 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		g_sig_catcher = 0;
		errno = 0;
		if (!gere_sig(READING_LINE))
			return (0);
		line = read_prompt(new_env);
		if (!line)
			break ;
		line = tatu_ferme_tes_guillemets(line);
		if ((line && !handle_line(line, new_env)) || (!line
				&& big_error()))
			break ;
		rl_on_new_line();
	}
	close(TTY_SAVED_FD);
	(ft_lstclear(&new_env, free), rl_clear_history());
	return (errno);
}
