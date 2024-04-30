#include "minishell.h"

char	*out_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		i;
	char	**testons;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	*itterand++ = '\0';
	testons = ft_split(itterand, ' ');
	i = 0;
	while (testons[i + 1] != NULL)
		free(testons[i++]);
	printf("dat's de one : %s\n", testons[i]);
	fd = open(testons[i], O_WRONLY | O_CREAT | O_TRUNC);
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (free(start_cmd), NULL);
	close(fd);
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
	while (testons + 1 != NULL)
		free(testons++);
	fd = open(*testons, flags);
	(free(*testons), free(testons));
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))
		return (free(start_cmd), NULL);
	close(fd);
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
	while (testons + 1 != NULL)
		free(testons++);
	fd = open(*testons, flags);
	if (fd = -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))
		return (free(start_cmd), NULL);
	close(fd);
	return (start_cmd);
}

t_stof	*str_to_func()
{
	t_stof	*ret;

	ret = malloc(sizeof(t_stof) * 6);
	ret[0].str = "<";
	ret[0].func = &in_handler;
	ret[1].str = ">";
	ret[1].func = &out_handler;
	ret[2].str = "<<";
	ret[2].func = &append_handler;//ceci est a gerer
	ret[3].str = ">>";
	ret[3].func = &append_handler;
	ret[4].str = NULL;
	ret[4].func = NULL;
	return (ret);
}