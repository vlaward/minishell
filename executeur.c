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
	int		fd;
	int		flags;

	status = 0;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			fd = open("test", flags, S_IRWXO);//concretement la ca gere les authorisation etc... avec un open moded
			if (fd == -1)
				return (printf("wait a minute... something aint right\n"));
			dup2(fd, STDOUT_FILENO);//maybe protect the dup ? Donno how it could fail but still
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 

}

int	in_handler(t_list *list)
{
	int		status;
	int		fd;
	int		falgs;

	falgs = O_RDONLY;
	status = 0;
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			fd = open("test", flags);//concretement la ca gere les authorisation etc... avec un open moded
			if (fd == -1)
				return (printf("wait a minute... something aint right\n"));
			dup2(fd, STDIN_FILENO);//fd in other line so test open fail
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 

}

int	append_handler(t_list *list)
{
	int		status;
	int		fd;
	int		falgs;

	status = 0;
	falgs = O_WRONLY | O_CREAT | O_APPEND;
	printf("e pourtant !!\n");
	if (!ft_strcmp(list->content, "exec"))
	{
		if (!fork())
		{
			fd = open("test", flags, S_IRWXO);//concretement la ca gere les authorisation etc... avec un open moded
			if (fd == -1)
				return (printf("wait a minute... something aint right\n"));
			dup2(fd), STDOUT_FILENO);
			execute_wpath(list->next->content);
		}
		else
			while( wait(&status) > 0);
	}
	//le close a metre la 

}

t_stof	*str_to_func()
{
	t_stof	*ret;

	ret = malloc(sizeof(t_stof) * 6);
	ret[2].str = "<";
	ret[2].func = &in_handler;
	ret[3].str = ">";
	ret[3].func = &out_handler;
	ret[4].str = "<<";
	ret[4].func = &pipe_handler;
	ret[5].str = ">>";
	ret[5].func = &append_handler;
	ret[6].str = NULL;
	ret[6].func = NULL;
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
		if (!ft_strncmp(stof->str, list->content, ft_strlen(list->content)))
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
