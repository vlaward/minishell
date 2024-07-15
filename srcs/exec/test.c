#include "../../includes/minitest.h"

int	parser(char *line, int flag, t_list *env);

int     execute_cmd(char **args, t_list *env) 
{
	char	**paths;
	char	*tmp;
	int		i;

	for (int i = 0; args[i]; i++)
		printf("arg %d is %s\n", i, args[i]);

	close(TTY_SAVED_FD);
	if (!args || *args == NULL)
		exit(0);
	/*if (ft_is_builtins(args[0]))
	{
		printf("is builtins\n");
		ft_builtins(args);
		return (0);
	}*/
	if (!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0], "/", 1))
		return (execve(args[0], args, NULL), 127);
	paths = ft_split(ft_getenv("PATH", env), ':');//si on est pas trop con on fait ca avec le nouvel env
	if (!paths)
	{
		exit(fprintf(stderr, "%s : command not found\n", args[0]));
	}
	tmp = ft_strjoin("/", args[0]);
	i = 0;
	while (paths[i] != NULL)//peut etre mettre un compteur avec i pars ce que si tout est incorecte et que il y a une erreur. il nme faut quand meme pas de leaks
	{
		free(args[0]);
		args[0] = ft_strjoin(paths[i], tmp);
		execve(args[0], args, NULL);
		free(paths[i++]);
	}
	i = 0; 
	fprintf(stderr, "%s : command not found\n", args[0]);
	while (args[i])
		free(args[i++]);
	(free(args), free(paths), free(tmp));
	exit(127);
	return (0);
}

char	**pars_command(char *cmd, t_list *env)
{//c'est pars command qui doit faire le free de cmd. pars ce que dans env_handler, je free cmd, et je renvoie une nouvelle chaine de char. vuala
	int		index;

	fprintf(stderr, "ah bah ca passe au moins la\n");
	if (!gere_sig(EXECUTING_CMD))
		return (NULL);
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '$')
			env_handler(&cmd, &index, env);
		else if (cmd[index] == '\"' || cmd[index] == '\'' )
			guille_handler(&cmd, &index, 0, env);
		else if (cmd[index] == '>' || cmd[index] == '<')
		{
			return (free(cmd), NULL);
		}
		else if (cmd[index] != '\0')
			index++;  
	}
	return (ft_minisplit(cmd));
}

int	fork_thing(char *line, int start, int itt, t_list *env)
{
	int		pid;
	int		pipette[2];

	pipe(pipette);
	line[itt] = '\0';
	//	splat = pars commande
	//le redirecte = parser la commande
	pid = fork();
	if (pid == -1)
		return (printf("NIQUE BIEN TQ GRQND MERER SQLQLRLKWEQAEHQEAtr\n"), -1);
	if (pid)
	{
		//	dup what's savec of the tty 
		dup2(pipette[0], STDIN_FILENO);
		(close(pipette[1]), close(pipette[0]));
		//printf("\n\nca passe pars la mais claaaairement : %s\n\n", &(line[itt + 1]));
		return (parser(line, itt + 1, env));
	}
	//dup2 le redirecte 
	//si pas d'autre redirecte
		dup2(pipette[1], STDOUT_FILENO);
	(close(pipette[1]), close(pipette[0]));
	exit(execute_cmd(pars_command(ft_strdup(&(line[start])), env), env));
}

int	parser(char *line, int start, t_list *env)
{//ici return 0 = tout c'est bien passe. Pars ce qu'on renvois $?
	int		status;
	int		itt;

	if (*line == '\0')
	 	return (free(line), 0);
	status = 0;
	itt = start;
	while (line[itt] != '|' && line[itt] != '\0')
		itt++;
	if (line[itt] && line[itt] == '|')
		return (fork_thing(line, start, itt, env));
	if (fork())// a securiser mais vas y ntm
	{
		if (!gere_sig(0))
			return (0);
		close(STDIN_FILENO);
		while(wait(&status) != -1);
		status = WEXITSTATUS(status);
		free(line);
		dup(TTY_SAVED_FD);
		return (0);//mettre status dans $?
	}
	exit(execute_cmd(pars_command(ft_strdup(&(line[start])), env), env));
}

void	free_cmd(void *afree)
{
	if (!afree)
		return ;
	free(((t_cmd *)afree)->cmd);
	free(afree);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	char	*cwd;
	t_list	*new_env;
	t_list	*cmd;

	(void)ac;
	(void)av;
	new_env = init_env(env);
	cwd = ft_calloc(sizeof(char), PATH_MAX);//verifie si pathmax est overflow pars un unicode
	if (!cwd)
		return (perror("calloc"), 0);
 	line = NULL;
	prompt = NULL;
	while (1)
	{
		if (!gere_sig(READING_LINE))
			return (0);
		ft_bzero(cwd, sizeof(char) * PATH_MAX);
		getcwd(cwd, PATH_MAX * sizeof(char));
		if (ft_strncmp(cwd, prompt, ft_strlen(cwd)) != 0)
		{
			free(prompt);
			prompt = ft_strjoin(cwd, "> ");
		}
		line = readline(prompt);
		if (!line)
			break ; //127
		line = tatu_ferme_tes_guillemets(line);
		if (line)
		{
			add_history(line);// <==  c'est plus la mais je laisse pars secu. Nrmlmt d'est dans tatusferme les guillemets
			fprintf(stderr, "ah bah ca passe au moins la\n");
			cmd = init_cmd(line, new_env);
			t_list	*tmp = cmd;
			while (tmp)
			{
				if (tmp->content)
					printf("nous avons lacmd : %s\nensuite in : %d\net enfin in : %d\n", ((t_cmd *)(tmp->content))->cmd, ((t_cmd *)(tmp->content))->in, ((t_cmd *)(tmp->content))->out);
				tmp = tmp->next;
			}
			
			ft_lstclear(&cmd, free_cmd);
			//	if (parser(line, 0, new_env) != 0)
			//		return (1);
			rl_on_new_line();
		}
	}
	ft_lstclear(&new_env, free);
	rl_clear_history();
	(free(cwd), free(prompt));
	return (0);
}