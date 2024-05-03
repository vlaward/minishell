#include "minishell.h"

char	*file_name_trim(char *str)
{
	char	*ret;

	fprintf(stderr, "Nahla est passe par ici\n");
	while (*str == ' ')
		str++;
	ret = str;
	while (*str && !ft_isin_table(*str, ">< "))
		str++;
	if (str == ret)
		return (NULL);
	ret = ft_strndup(ret, str - ret + 1);
	fprintf(stderr, "voici le nom du file : \'%s\'\n", ret);
	return (ret);
}

char	*out_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	int		i;
	char	**file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	*itterand++ = '\0';
	file = ft_split(itterand, ' ');
	if (!file || ft_isin_table(**file, "><"))//a preciser. Das le cas  "ls > te>st" il vas tenter de mettre dans "te>st" au lieu de creer "te" et "st" et mettre le tout dans le dernier
		return (fprintf(stderr, "there is no... there is no file to point to\n"), NULL);
	i = 0;
	while (file[i + 1] != NULL)
		free(file[i++]);
	fd = open(file[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (NULL);
	close(fd);
	return (start_cmd);
}

char	*in_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	char	*file;

	status = 0;
	*itterand++ = '\0';
	file = file_name_trim(itterand);
	ft_strlcpy(file, file, itterand - file + 1);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))
		return (NULL);
	close(fd);
	return (start_cmd);
}

char	*append_handler(char *itterand, char *start_cmd)
{
	int		status;
	int		fd;
	char	**file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref

	status = 0;
	*itterand = '\0';
	itterand += 2;
	file = ft_split(itterand, ' ');
	while (*itterand == ' ')
		itterand++;
	while (!ft_isin_table(*itterand, ">< "))
		itterand++;
	if (!file || ft_isin_table(**file, "><"))
		return (fprintf(stderr, "there is no... there is no file to point to\n"), NULL);
	fd = open(*file, O_RDWR| O_APPEND | O_CREAT, S_IRWXO);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (!dup2(fd, STDOUT_FILENO))//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
		return (NULL);
	close(fd);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
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