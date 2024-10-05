/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:37:25 by ncrombez          #+#    #+#             */
/*   Updated: 2024/09/30 02:33:15 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitest.h"

int	parser(t_list **cmd, t_list *env);

char	**pars_command(t_list *cmd, t_list *env)
{//c'est pars command qui doit faire le free de cmd. pars ce que dans env_handler, je free cmd, et je renvoie une nouvelle chaine de char. vuala
	char	*str;
	
	if (((t_cmd *)(cmd->content))->in && dup2(((t_cmd *)(cmd->content))->in, STDIN_FILENO) == -1)
			return (perror("dup2 "), NULL);
	if (((t_cmd *)(cmd->content))->out && dup2(((t_cmd *)(cmd->content))->out, STDOUT_FILENO) == -1)
			return (perror("dup2"), NULL);
	if (((t_cmd *)(cmd->content))->in)
		close(((t_cmd *)(cmd->content))->in);
	if (((t_cmd *)(cmd->content))->out)
		close(((t_cmd *)(cmd->content))->out);
	str = ((t_cmd *)(cmd->content))->cmd;
	free(cmd->content);
	free(cmd);
	return (ft_minisplit(str, env));
}

int	fork_thing(t_list *cmd, t_list *env)
{
	int		pid;
	int		pipette[2];
	t_list	*tmp;

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
		return (parser(&tmp, env));
	}
	ft_lstclear(&(cmd->next), free_cmd);
	dup2(pipette[1], STDOUT_FILENO);
	(close(pipette[1]), close(pipette[0]));
	exit(execute_cmd(pars_command(cmd, env), env));
}

int	parser(t_list **cmd, t_list *env)
{//ici return 0 = tout c'est bien passe. Pars ce qu'on renvois $?
	int		status;

	if ((*cmd)->next)
		return (fork_thing(*cmd, env));
	if(!((t_cmd*)((*cmd)->content))->has_pipe)
		if (ft_builtins(((t_cmd*)((*cmd)->content))->cmd) != NULL)
			return(ft_builtins(((t_cmd *)((*cmd)->content))->cmd)(cmd, env, ft_minisplit(ft_strdup(((t_cmd *)((*cmd)->content))->cmd), env)));
	status = 0;
	if (fork())// a securiser mais vas y ntm
	{
		if (!gere_sig(0))
			return (0);
		while(wait(&status) != -1)
		{
			ft_lstclear(cmd, free_cmd);
			if (WEXITSTATUS(status) != ft_atoi(env->content))
			{
				free(env->content);
				env->content = ft_itoa(WEXITSTATUS(status));
				if (!env->content)
					return (perror("malloc"), 0);
			}
		}	
		close(STDIN_FILENO);
		dup(TTY_SAVED_FD);
		return (WEXITSTATUS(status));//mettre status dans $?
	}
	close(TTY_SAVED_FD);
	exit(execute_cmd(pars_command(*cmd, env), env));
}

char	*read_prompt(t_list *env)
{
	static char	prompt[PATH_MAX];
	char	*pwd;
	int		i;

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
	t_list	*cmd;
	int	exitcode;

	(void)ac;
	(void)av;
	new_env = init_env(env);
	line = NULL;
	dup(STDIN_FILENO);
	while (1)
	{
		if (!gere_sig(READING_LINE))
			return (0);
		line = read_prompt(new_env);
		if (!line)
			break ; //127
		line = tatu_ferme_tes_guillemets(line);
		if (line)
		{
			//add_history(line);// <==  c'est plus la mais je laisse pars secu. Nrmlmt d'est dans tatusferme les guillemets
			cmd = init_cmd(line, new_env);
			if (cmd)
			{
				exitcode = parser(&cmd, new_env);
				if (exitcode != ft_atoi(new_env->content))
				{
					free(new_env->content);
					new_env->content = ft_itoa(exitcode);
					if (!new_env->content)
					{
						perror("malloc");
						break ;
					}
				}
				// ft_lstclear(&cmd, free_cmd);
			}
		}
		rl_on_new_line();
	}
	close(TTY_SAVED_FD);
	ft_lstclear(&new_env, free);
	rl_clear_history();
	return (0);
}
