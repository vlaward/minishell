#include "minishell.h"
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

	if (!args || *args == NULL)
		exit(0);
	if (!ft_strncmp(args[0], "./", 2))
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

	stofs = str_to_func();
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '$')
			env_handler(&cmd, &index);
		if (cmd[index] == '\"' || cmd[index] == '\'' )
			guille_handler(&cmd, &index, 0);
		if (cmd[index] == '>' || cmd[index] == '<')
			if (!redirects(&cmd, &index, stofs, REDIRECT))
				return (free(stofs), free(cmd), NULL);
		if (cmd[index] != '\0')
			index++;  
	}
	free(stofs);
	return (ft_minisplit(cmd));
}

int	fork_thing(char *line, char *start_cmd)
{
	int		status;
	int		pid;
	int		pipette[2];

	pipe(pipette);
	*line = '\0';
	pid = fork();
	if (pid == -1)
		return (printf("NIQUE BIEN TQ GRQND MERER SQLQLRLKWEQAEHQEAtr\n"), -1);
	if (pid)
	{
		dup2(pipette[0], STDIN_FILENO);
		close(pipette[0]);
		close(pipette[1]);
		while(waitpid(pid, &status, WNOHANG) == 0)
			continue;
		return (parser(line + 1, NOT_FIRST_COMMAND));
	}
	else
	{
	 	dup2(pipette[1], STDOUT_FILENO);
		close(pipette[0]);
		close(pipette[1]);
		
	}
	return (execute_cmd(pars_command(start_cmd)));
}

int	parser(char *line, int flag)
{//ici return 0 = tout c'est bien passe. Pars ce qu'on renvois $?
	char	*start_cmd;
	int		status;
	int		chpid;

	if (*line == '\0')
		return (free(line), 0);
	status = 0;
	if (flag == FIRST_COMMAND)
	{
		chpid = fork();
		if (chpid)
		{
			while(waitpid(chpid, &status, WNOHANG) == 0)
				continue;
			status = WEXITSTATUS(status);
			free(line);
			return (0);//mettre status dans $?
		}
	}
	start_cmd = ft_strdup(line);
	line = start_cmd;
	while (*line != '|' && *line != '\0')
		line++;
	if (*line && *line == '|')
		return (fork_thing(line, start_cmd));
	return (execute_cmd(pars_command(start_cmd)));
}

int	main()
{
	char	*line;
	char	*prompt;
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX);//verifie si pathmax est overflow pars un unicode
	line = NULL;//poiur valgrind. option en commentaire c pour enlever le problemme valgrind ?
	prompt = NULL;
	while (1)// add signal global test
	{
		ft_bzero(cwd, sizeof(char) * PATH_MAX);
		getcwd(cwd, PATH_MAX * sizeof(char));
		if (ft_strncmp(cwd, prompt, ft_strlen(cwd)))
		{
			free(prompt);
			prompt = ft_strjoin(cwd, "> ");
		}
		line = readline(prompt);
		line = tatu_ferme_tes_guillemets(line);//est ce que reqdline plante ?
		if (line)
		{
			add_history(line);
			if (all_good(ft_strdup(line)))
				parser(line, FIRST_COMMAND);
		}
		rl_on_new_line();
	}
	(free(cwd), free(prompt));
	return (0);
}