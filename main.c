#include "minishell.h"
#ifndef PATH_MAX
# define PATH_MAX 4096
# endif

#define FIRST_COMMAND 0
#define NOT_FIRST_COMMAND 1

int	parser(char *line, int flag);
char	*env_handler(char *start_cmd);

int     execute_cmd(char **args)
{
	char	**paths;
	char	*tmp;
	int		i;
	int		status;

	if (!args || *args == NULL)
		exit(0);
	if (!ft_strncmp(args[0], "./", 2))//gerer aussi le /bin/moncul : relativ path
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

char	*redirects(char *itterand, char *start_cmd, t_stof *stofs)
{
	int	i;

	i = 0;
	while (itterand[i] == *itterand)
		if (i++ >= 2)
			return (fprintf(stderr, "error ya 3 fois le meme signe frero\n"), free(start_cmd), free(stofs), NULL);//a savoir dans quel sens je met les free (que je double free pas dans la fonction appellante)
	while (stofs->str)
	{
		if (!ft_strncmp(stofs->str, itterand, i))
			break;
		stofs++;
	}
	printf("wii uze ze fukchion : %s\n", stofs->str);
	if (stofs->func != NULL)
		start_cmd = stofs->func(itterand, start_cmd);//comme ca il enleve d lui meme la partie qu'il aime pas
	return (start_cmd);//pas besoin de gerer une erreur dans func, si il y en a une func renverras NULL. Donc c'est gerer auto
}

char	*do_this_env(char *start_cmd, char *itterand)
{
	char	*start_env;
	char	*env_key;
	char	*env_value;
	char	*tmp_cmd;

	*itterand++ = '\0';
	start_env = itterand;
	while (*itterand && !ft_isin_table(*itterand, "\'\"<>$ "))//LISTE A VERIFIER <======== !!!!!!
		itterand++;
	env_key = ft_calloc(itterand - start_env + 2, sizeof(char));
	ft_strlcpy(env_key, start_env, itterand - start_env + 1);
	env_value = getenv(env_key);//peut etre besoin d'un strcpy mais pas besoin de securiser si env existe pas, il renverras juste NULL
	tmp_cmd = ft_strjoin(start_cmd, env_value);// devoir rajouter un espace peut etre ?
	free(env_key);
	itterand = ft_strjoin(tmp_cmd, itterand);
	(free(start_cmd), free(tmp_cmd));
	return (env_handler(itterand));
}

char	*env_handler(char *start_cmd)
{
	char	*itterand;
	int		i;

	itterand = start_cmd;
	while (*itterand != '\0')
	{
		i = 1;
		if (*itterand == '\'')
		{
			while (itterand[i] != '\0' && itterand[i] != *itterand)//pas besoin de verifier si itterand finis a '\0'. pars command le fait deja
				i++;
			itterand = &itterand[i];
		}
		if (*itterand == '$')
			return(do_this_env(start_cmd, itterand));
		itterand++;
	}
	return (start_cmd);
}

char	**pars_command(char *cmd)
{//c'est pars command qui doit faire le free de cmd. pars ce que dans env_handler, je free cmd, et je renvoie une nouvelle chaine de char. vuala
	t_stof	*stofs;
	char	*start_cmd;
	int		i;

	stofs = str_to_func();//maybe put it in main ? not to do it evrytime, save time. And if we put evrything in a struct in the end
	start_cmd = cmd;
	while (*cmd)
	{
		i = 1;
		if (ft_isin_table(*cmd, "\"\'"))
		{
			while (cmd[i] != '\0' && cmd[i] != *cmd)
				i++;
			if  (cmd[i] == '\0')
				return (NULL);//surement un free ou deux a faire la
			cmd = &cmd[i];
		}
		if (*cmd == '>' || *cmd == '<')
			start_cmd = redirects(cmd, start_cmd, stofs);
		if (start_cmd == NULL)
			return (NULL);
		cmd++;
	}
	free(stofs);
	return (ft_minisplit(env_handler(start_cmd)));
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
		waitpid(pid, &status, 0);
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
	start_cmd = line;
	if (flag == FIRST_COMMAND)
	{
		chpid = fork();
		if (chpid)
		{
			waitpid(chpid, &status, 0);
			status = WEXITSTATUS(status);
			free(line);
			return (0);//mettre status dans $?
		}
	}
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
		line = tatu_ferme_tes_guillemets(readline(prompt));//est ce que reqdline plante ?
		if (line)
		{
			add_history(line);
			parser(line, FIRST_COMMAND);
		}
		rl_on_new_line();
	}
	(free(cwd), free(prompt));
	return (0);
}