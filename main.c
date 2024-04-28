#include "minishell.h"
#ifndef PATH_MAX
# define PATH_MAX 4096
# endif

#define FIRST_COMMAND 0
#define NOT_FIRST_COMMAND 0

int     execute_cmd(char **args, int flags)
{
	char	**paths;
	char	*tmp;
	char	*args_0;
	int		status;

	if (flags == FIRST_COMMAND)
		if (fork())
			return (wait(&status), 1);
	if (!ft_strncmp(args[0], "./", 2))
		return (execve(args[0], args, NULL));
	paths = ft_split(getenv("PATH"), ':');
	args_0 = ft_strdup(args[0]);
	tmp = ft_strjoin("/", args[0]);
	while (*paths != NULL)//peut etre mettre un compteur avec i pars ce que si tout est incorecte et que il y a une erreur. il nme faut quand meme pas de leaks
	{
		args[0] = ft_strjoin(*paths++, tmp);
		execve(args[0], args, NULL);
		 free(args[0]);
	}
	return (0);
}

char	*redirects(char *itterand, char *start_cmd, t_stof *stofs)
{
	int	i;

	i = 1;
	while (itterand[i - 1] == *itterand)
		if (i++ >= 2)
			return (free(start_cmd), free(stofs), NULL);//a savoir dans quel sens je met les free (que je double free pas dans la fonction appellante)
	while (stofs->str)
		if (!ft_strncmp((stofs++)->str, itterand, i))
			break;
	start_cmd = stofs->func(itterand + i, start_cmd);//comme ca il enleve d lui meme la partie qu'il aime pas
	return (start_cmd);//pas besoin de gerer une erreur dans func, si il y en a une func renverras NULL. Donc c'est gerer auto
}

char	*do_this_env(char **start_cmd, char *itterand)
{
	char	*start_env;
	char	*env_key;
	char	*env_value;
	char	*tmp_cmd;

	*itterand++ = '\0';
	start_env = itterand;
	while (!ft_isin_table(*itterand, "\'\"<>$"))//LISTE A VERIFIER <======== !!!!!!
		itterand++;
	env_key = ft_calloc(itterand - start_env + 1, sizeof(char));
	ft_strlcpy(env_key, start_env, itterand - start_env);
	env_value = getenv(env_key);//peut etre besoin d'un strcpy mais pas besoin de securiser si env existe pas, il renverras juste NULL
	tmp_cmd = ft_strjoin(*start_cmd, env_value);// devoir rajouter un espace peut etre ?
	(free(*start_cmd), free(env_value), free(env_key));
	*start_cmd = ft_strjoin(tmp_cmd, itterand);//peu etre chelou a faire
	free(tmp_cmd);
	return (itterand);
}

char	env_handler(char *start_cmd)
{
	char	*ret;
	char	*itterand;
	int		i;

	itterand = start_cmd;
	while (*itterand != 0)
	{
		i = 1;
		if (ft_isin_table(*itterand, "\"\'"))
		{
			while (itterand[i] != '\0' && itterand[i] != *itterand)//pas besoin de verifier si itterand finis a '\0'. pars command le fait deja
				i++;
			itterand = &itterand[i];
		}
		if (*itterand == '$')
		itterand = do_this_env(&start_cmd, itterand);
		itterand++;
	}
	return (ret);
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
	if (*cmd is in "><")
			start_cmd = redirects(&cmd, start_cmd);
		if (start_cmd == NULL)
			return (NULL);
		cmd++;
	}
	free(stofs);
	return (ft_minisplit(env_handler(start_cmd)));
}

int	fork_thing(char *line)
{
	int		status;
	int		pid;
	int		pipette[2];

	pipe(pipette);
	status = 0;
	*line = '\0';
	pid = !fork();
	if (pid = -1)
		return (-1);
	if (!pid)
	{
		dup2(pipette[0], STDIN_FILENO);
		parser(line + 1, NOT_FIRST_COMMAND);
	}
	else
		dup2(pipette[1], STDOUT_FILENO);
	return (pid);
}

int	parser(char *line, int flag)//le flag c'est pour savoir si on est sur la premiere itteration ou une autre. pour la premiere ittertion on doit fork pour le exece  sinon on perds le prompt
{//flag : 0 = first itteratio ; 1 = seconde+ iteration
	char	*start_cmd;

	start_cmd = line;
	while (*line != '|' && *line++ != '\0');//autorisee et marche ?
	if (*line == '|')
		if (fork_thing(line) == -1)

	if (!execute_cmd(pars_command(start_cmd), flag))
		return (0);//depends code erreur ?
	return (free(start_cmd), 1);
}

int	main()
{
	char	*line;
	char	*prompt;

	prompt = ft_calloc(sizeof(char), PATH_MAX);//verifie si pathmax est overflow pars un unicode
	getcwd(prompt, PATH_MAX * sizeof(char));
	prompt = ft_strjoin(prompt, "> ");
	line = NULL;//poiur valgrind. option en commentaire c pour enlever le problemme valgrind ?
	while (1)// add signal global test
	{
		line = tatu_ferme_tes_guillemets(readline(prompt));//est ce que reqdline plante ?
		add_history(line);
		parser(line, FIRST_COMMAND);
		rl_on_new_line();
	}	
	return (0);
}