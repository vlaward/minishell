#include "minishell.h"

char	*out_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		i;
	char	**file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	*itterand++ = '\0';
	file = ft_split(itterand, ' ');
	if (!file || ft_isin_table(**file, "><"))
		return (fprintf(stderr, "there is no... there is no file to point to\n"), NULL);
	i = 0;
	while (file[i + 1] != NULL)
		free(file[i++]);
	fd = open(file[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXO);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (NULL);
	close(fd);
	return (start_cmd);
}

// int	out_handler(t_list *list)
// {
// 	int		status;
// 	int		fd;
// 	int		flags;

// 	status = 0;
// 	flags = O_WRONLY | O_CREAT | O_TRUNC;
// 	if (!ft_strcmp(list->content, "exec"))
// 	{
// 		if (!fork())
// 		{
// 			fd = open("test", flags, S_IRWXO);//concretement la ca gere les authorisation etc... avec un open moded
// 			if (fd == -1)
// 				return (printf("wait a minute... something aint right\n"));
// 			dup2(fd, STDOUT_FILENO);//maybe protect the dup ? Donno how it could fail but still
// 			execute_wpath(list->next->content);
// 		}
// 		else
// 			while( wait(&status) > 0);
// 	}
// 	//le close a metre la 

// }

char	*in_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	char	*file;

	status = 0;
	*itterand++ = '\0';
	file = itterand;
	while (!ft_isin_table(*itterand, ">< "))
		itterand++;
	ft_strlcpy(file, file, itterand - file + 1);
	fd = open(file, O_RDONLY);
	free(file);
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
	int		i;
	char	**file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	printf("ehe te nedayoo \n");
	status = 0;
	*itterand = '\0';
	itterand += 2;
	file = ft_split(itterand, ' ');
	if (!file || ft_isin_table(**file, "><"))
		return (fprintf(stderr, "there is no... there is no file to point to\n"), NULL);
	i = 0;
	while (file[i + 1] != NULL)
		free(file[i++]);
	fd = open(file[i], O_APPEND);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (NULL);
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