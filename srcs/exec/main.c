#include "../../includes/minishell.h"
#ifndef PATH_MAX
# define PATH_MAX 4096
# endif

#define FIRST_COMMAND 0
#define NOT_FIRST_COMMAND 1
#define REDIRECT 1

int	parser(char *line, int flag);

int     execute_cmd(char **args)
{
	char	**paths;
	char	*tmp;
	int		i;

	close(TTY_SAVED_FD);
	if (!args || *args == NULL)
		exit(0);
	if (!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0], "/", 1))
		return (execve(args[0], args, NULL), 127);
	paths = ft_split(getenv("PATH"), ':');
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
	printf("%s : command not found\n", tmp + 1);
	while (args[i])
		free(args[i++]);
	(free(args), free(paths), free(tmp));
	exit(127);
	return (0);
}

char	**pars_command(char *cmd)
{//c'est pars command qui doit faire le free de cmd. pars ce que dans env_handler, je free cmd, et je renvoie une nouvelle chaine de char. vuala
	t_stof	*stofs;
	int		index;

	if (!gere_sig(EXECUTING_CMD))
		return (NULL);
	stofs = str_to_func();
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '$')
			env_handler(&cmd, &index);
		else if (cmd[index] == '\"' || cmd[index] == '\'' )
			guille_handler(&cmd, &index, 0);
		else if (cmd[index] == '>' || cmd[index] == '<')
		{
			if (!redirects(&cmd, &index, stofs, REDIRECT))
				return (free(stofs), free(cmd), NULL);
		}
		else if (cmd[index] != '\0')
			index++;  
	}
	free(stofs);
	return (ft_minisplit(cmd));
}

int	fork_thing(char *line, int start, int itt)
{
	int		pid;
	int		pipette[2];

	pipe(pipette);
	line[itt] = '\0';
	pid = fork();
	if (pid == -1)
		return (printf("NIQUE BIEN TQ GRQND MERER SQLQLRLKWEQAEHQEAtr\n"), -1);
	if (pid)
	{
		close(pipette[1]);
		dup2(pipette[0], STDIN_FILENO);
		close(pipette[0]);
		printf("\n\nca passe pars la mais claaaairement : %s\n\n", &(line[itt + 1]));
		return (parser(line, itt + 1));
	}
	else
	{
	 	close(pipette[0]);
		dup2(pipette[1], STDOUT_FILENO);
		close(pipette[1]);
		
	}
	exit(execute_cmd(pars_command(ft_strdup(&(line[start])))));
}

int	parser(char *line, int start)
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
		return (fork_thing(line, start, itt));
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
	exit(execute_cmd(pars_command(ft_strdup(&(line[start])))));
}

int	main()
{
	char	*line;
	char	*prompt;
	char	*cwd;
	int		tmp_sdin;

	cwd = ft_calloc(sizeof(char), PATH_MAX);//verifie si pathmax est overflow pars un unicode
	if (!cwd)
		return (perror("calloc"), 0);
	line = NULL;//poiur valgrind. option en commentaire c pour enlever le problemme valgrind ?
	prompt = NULL;
	fprintf(stderr, "vboici le fd enregistre : %d\n", dup(STDIN_FILENO));//pour garder le tty en tant que fd 3 for latter use
	while (1)// add signal global test
	{
		if (!gere_sig(READING_LINE))
			return (0);
		ft_bzero(cwd, sizeof(char) * PATH_MAX);
		getcwd(cwd, PATH_MAX * sizeof(char));
		if (ft_strncmp(cwd, prompt, ft_strlen(cwd)))
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
			tmp_sdin = dup(STDIN_FILENO);
			//add_history(line); <==  c'est plus la mais je laisse pars secu. Nrmlmt d'est dans tatusferme les guillemets
			if (all_good(ft_strdup(line)))
				if (parser(line, 0) != 0)
					return (1);
			dup2(tmp_sdin, STDIN_FILENO);
			rl_on_new_line();
		}
	}
	rl_clear_history();
	(free(cwd), free(prompt));
	return (0);
}