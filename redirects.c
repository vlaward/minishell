#include "minishell.h"

char	*file_name_trim(char **str)
{
	char	*ret;

	while (**str == ' ')
		(*str)++;
	ret = *str;
	while (**str && !ft_isin_table(**str, ">< "))
		(*str)++;
	if (*str == ret)
		return (NULL);
	return (ft_strndup(ret, *str - ret));
}

char	*out_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;


	*itterand++ = '\0';
	file = file_name_trim(&itterand);
	while (file != NULL)
	{
		fprintf(stderr, "this is the name : %s\n", file);
		if (file == NULL)
			return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
		free(file);
		if (fd == -1)
			return(printf("wait a minute... something aint right\n"), NULL);
		else if (dup2(fd, STDOUT_FILENO) == -1)
			return (NULL);
		close(fd);
		file = file_name_trim(&itterand);
	}
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

char	*in_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;


	*itterand++ = '\0';
	file = file_name_trim(&itterand);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
		return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (dup2(fd, STDIN_FILENO) == -1)
		return (NULL);
	close(fd);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}

char	*append_handler(char *itterand, char *start_cmd)
{
	int		fd;
	char	*file;//je pense que ca fait bcp de malloc pour rien. On pourrai avancer jusqu'au dernier mot, free apres le dernier mot, mettre l'iterand en option et free la itterand. bref


	*itterand = '\0';
	itterand += 2;
	file = file_name_trim(&itterand);
	if (file == NULL)
		return (fprintf(stderr, "there aint no file bud ;-;\n"), NULL);
	fd = open(file, O_RDWR| O_APPEND | O_CREAT, S_IRWXO);
	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), NULL);
	else if (dup2(fd, STDOUT_FILENO) == -1)//a voir si il faut pas utiliser STDOUT_FILENO en miniscule j'en suis presque sur
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
	ret[2].func = NULL;
	ret[3].str = ">>";
	ret[3].func = &append_handler;
	ret[4].str = NULL;
	ret[4].func = NULL;
	return (ret);
}