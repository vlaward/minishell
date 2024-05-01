#include "minishell.h"

int	execute_wpath(char **args)
{//si cette fonction return... c'est pas normal T^T c'est que l'executable est introuvable donc surement inexistant(mini chance pour que ca soit a cause de problemes d'allocation de memoire du cote hardware quoi)
	char	**paths;
	char	*tmp;
	char	*args_0;

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

int	pipe_handler(t_list *list)
{
	printf("voici le contenus du premier element de la liste... c'est parfeaitement inutil : %s\n", (char *)list->content);
	printf("bigget fucking placeholder\n");
	return (1);
}

int	out_handler(t_list *list)
{
	int		status;

	status = 0;
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			dup2(open("txt", O_WRONLY | O_CREAT), STDOUT_FILENO);
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 
	return (0); // return at end of int fct
}

int	in_handler(t_list *list)
{
	int		status;

	status = 0;
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			dup2(open("txt", O_RDONLY), STDIN_FILENO);//fd in other line so test open fail
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 
	return (0); // return at end of int fct
}

int	append_handler(t_list *list)
{
	int		status;

	status = 0;
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			dup2(open("txt", O_WRONLY | O_CREAT | O_APPEND), STDOUT_FILENO);
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 
	return (0); // return at end of int fct
}

t_stof	*str_to_func()
{
	t_stof	*ret;

	ret = malloc(sizeof(t_stof) * 6);
	ret[0].str = "|";
	ret[0].func = &pipe_handler;
	ret[1].str = "<";
	ret[1].func = &in_handler;
	ret[2].str = ">";
	ret[2].func = &out_handler;
	ret[3].str = "<<";
	ret[3].func = &pipe_handler;
	ret[4].str = ">>";
	ret[4].func = &append_handler;
	ret[5].str = NULL;
	ret[5].func = NULL;
	return (ret);
}

int	executeur(t_list *list)
{
	t_stof	*stof;
	pid_t	chpid;
	int		status = 0;

	stof = str_to_func();
	while (stof->str != NULL)
	{
		if (!ft_strcmp(stof->str, list->content))
				break;
		stof++;
	}
	if (stof->str == NULL)
	{
		chpid = fork();
		if (!chpid)
		{
			if (!execute_wpath(list->next->content))
				return (0);
		}
		else
			while (wait(&status) > 0);
	}
	else
	{
		stof->func(list->next);
	}
	return (1);
}
