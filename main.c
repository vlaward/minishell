#include "minishell.h"
#ifndef PATH_MAX
# define PATH_MAX 4096
# endif

#define FIRST_COMMAND 0
#define NOT_FIRST_COMMAND 0

int		execve_cmd(char **command, int flag)
{
	if (option == FIRST_COMMAND)
		if (fork())
			wait();
	exec;
}

char	*redirects(cahr **cmd, char *start_cmd)
{

	return (string_without_redirect)
}

char	**pars_command(char *cmd)
{
	t_stof	*stofs;
	char	*start_cmd;

	stofs = str_to_func();//maybe put it in main ? not to do it evrytime, save time. And if we put evrything in a struct in the end
	while (*cmd)
	{
		if (*cmd is in "><")
			start_cmd = redirects(&cmd, start_cmd);
		cmd++;
	}
	free();
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
		line = readline(prompt);//est ce que reqdline plante ?

		add_history(line);
		parser(line, FIRST_COMMAND);
		rl_on_new_line();
	}	
	return (0);
}