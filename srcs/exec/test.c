#include "../../includes/minitest.h"

int	parser(t_list *cmd, t_list *env);

char	**env_to_tabl(t_list *env)
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

int     execute_cmd(char **args, t_list *env) 
{
	char	**paths;
	char	*tmp;
	char	**tabl_env;
	int		i;

	if (!args)
	{
		fprintf(stderr, "Mais weeeesh T^T\n");
		exit(errno);
	}
	if (!args || *args == NULL)
		exit(0);
	if (ft_builtins(args[0]))//un ft_strcmp
		exit(ft_builtins(args[0])(NULL, env, args));
	
	/*if (ft_is_builtins(args[0]))
	{
		printf("is builtins\n");
		ft_builtins(args);
		return (0);
	}*/
	tabl_env = env_to_tabl(env);
	if (!tabl_env)
	{
		perror("malloc");
		exit(errno);
	}
	if (!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0], "/", 1))
		return (execve(args[0], args, tabl_env), 127);
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
		execve(args[0], args, tabl_env);
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

char	**pars_command(t_list *cmd, t_list *env)
{//c'est pars command qui doit faire le free de cmd. pars ce que dans env_handler, je free cmd, et je renvoie une nouvelle chaine de char. vuala
	if (((t_cmd *)(cmd->content))->in && dup2(((t_cmd *)(cmd->content))->in, STDIN_FILENO) == -1)
			return (perror("dup2 "), NULL);
	if (((t_cmd *)(cmd->content))->out && dup2(((t_cmd *)(cmd->content))->out, STDOUT_FILENO) == -1)
			return (perror("dup2"), NULL);
	if (((t_cmd *)(cmd->content))->in)
		close(((t_cmd *)(cmd->content))->in);
	if (((t_cmd *)(cmd->content))->out)
		close(((t_cmd *)(cmd->content))->out);
	return (ft_minisplit(&(((t_cmd *)(cmd->content))->cmd), env	));
}

int	fork_thing(t_list *cmd, t_list *env)
{
	int		pid;
	int		pipette[2];

	pipe(pipette);
	pid = fork();
	if (pid == -1)
		return (printf("NIQUE BIEN TQ GRQND MERER SQLQLRLKWEQAEHQEAtr\n"), -1);
	if (pid)
	{
		dup2(pipette[0], STDIN_FILENO);
		(close(pipette[1]), close(pipette[0]));
		return (parser(cmd->next, env));
	}
	fprintf(stderr, "pardon???\n");
	printf("voici ce qu'est sense etre la putain de ligne : %s\n", ((t_cmd *)(cmd->content))->cmd);
	dup2(pipette[1], STDOUT_FILENO);
	(close(pipette[1]), close(pipette[0]));
	fprintf(stderr, "voici ce qu'est sense etre la putain de ligne : %s\n", ((t_cmd *)(cmd->content))->cmd);
	exit(execute_cmd(pars_command(cmd, env), env));
}

int	parser(t_list *cmd, t_list *env)
{//ici return 0 = tout c'est bien passe. Pars ce qu'on renvois $?
	int		status;

	if (cmd->next)
		return (fork_thing(cmd, env));
	if(!((t_cmd*)(cmd->content))->has_pipe)
		if (ft_builtins(((t_cmd *)(cmd->content))->cmd) != NULL)
		{
			fprintf(stderr, "\n\nNUUGHUUUUUGH\n\n");
			return(ft_builtins(((t_cmd *)(cmd->content))->cmd)(cmd->content, env, pars_command(cmd, env)));
		}
	status = 0;
	if (fork())// a securiser mais vas y ntm
	{
		if (!gere_sig(0))
			return (0);
		while(wait(&status) != -1);
		status = WEXITSTATUS(status);
		close(STDIN_FILENO);
		dup(TTY_SAVED_FD);
		return (0);//mettre status dans $?
	}
	exit(execute_cmd(pars_command(cmd, env), env));
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
		fprintf(stderr, "si ca se trouve ca passe meme pas par la\n");
		line = tatu_ferme_tes_guillemets(line);
		if (line)
		{
			add_history(line);// <==  c'est plus la mais je laisse pars secu. Nrmlmt d'est dans tatusferme les guillemets
			cmd = init_cmd(line, new_env);
			if (cmd)
			{
				parser(cmd, new_env);
				ft_lstclear(&cmd, free_cmd);
			}
		}
		rl_on_new_line();
	}
	ft_lstclear(&new_env, free);
	rl_clear_history();
	return (0);
}