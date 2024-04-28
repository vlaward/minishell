#include "minishell.h"

char	*out_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		flags;
	char	**testons;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	*itterand++ = '\0';
	testons = ft_split(itterand, ' ');
	free(itterand);
	while (testons + 1 != NULL)
		free(testons++);
	fd = open(*testons, flags);
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, stdout->_fileno))//a voir si il faut pas utiliser stdout->_fileno en miniscule j'en suis presque sur
		return (free(start_cmd), NULL);
	return (start_cmd);
}

char	*in_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		flags;
	char	**testons;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	flags = O_RDONLY;
	*itterand++ = '\0';
	testons = ft_split(itterand, ' ');
	free(itterand);
	while (testons + 1 != NULL)
		free(testons++);
	fd = open(*testons, flags);
	(free(*testons), free(testons));
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, stdout->_fileno))
		return (free(start_cmd), NULL);
	return (start_cmd);
}

char	*append_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		flags;
	char	**testons;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	flags = O_WRONLY | O_CREAT | O_APPEND;
	*itterand++ = '\0';
	testons = ft_split(itterand, ' ');
	free(itterand);
	while (testons + 1 != NULL)
		free(testons++);
	fd = open(*testons, flags);
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, stdout->_fileno))
		return (free(start_cmd), NULL);
	return (start_cmd);
}

t_stof	*str_to_func()
{
	int		status;
	int		fd;
	int		flags;
	char	**testons;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la str. bref

	status = 0;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	testons = ft_split(str);
	while (teston + 1 != NULL)
		free(testons++);
	fd = open(testons, flags);
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"));
	else
		return (dup2(fd, stdout));
	return (fd);
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
