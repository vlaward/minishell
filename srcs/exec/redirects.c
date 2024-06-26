#include "../../includes/minishell.h"


//verifier si errno est bien a 0 a la base
int	in_handler(char **start_cmd, int *index, int flag)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM);
	//fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file),  0);
	else if (flag == REDIRECT)
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	if ( close(fd) == -1)
		return (perror("close"), 0);
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;// ici il faut free s_c avant. sinon c pas logique
	return (free(file), tmp != NULL);
}

int	append_handler(char **start_cmd, int *index, int flag)
{
	int		fd;
	char	*file;
	char	*tmp;

	(*start_cmd)[*index] = '\0';
	*index += 1;
	file = trim(start_cmd, index, F_NAME_TRIM);
	//fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (0);
	}
	fd = open(file, O_RDWR| O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
	if (fd == -1)
		return(perror("open"), 0);
	else if (flag == REDIRECT)
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	if ( close(fd) == -1)
		return (perror("close"), 0);
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;
	return (free(file), tmp != NULL);
}

int	out_handler(char **start_cmd, int *index, int flag)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM);
	//fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (0);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
	if (fd == -1)
		return(perror("open"), 0);
	else if (flag == REDIRECT)
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	if ( close(fd) == -1)
		return (perror("close"), 0);
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;
	return (free(file), tmp != NULL);
}


int	redirects(char **start_cmd, int *index, t_stof *stofs, int flag)
{
	int	i;

	i = 1 + ((*start_cmd)[*index] == (*start_cmd)[*index + 1]);
	while (stofs->str)
	{
		if (!ft_strncmp(stofs->str, &((*start_cmd)[*index]), i))
			break ;
		stofs++;
	}
	//fprintf(stderr, "wii uze ze fukchion : %s, %d\n", stofs->str, i);
	if (stofs->func != NULL)
		if (!stofs->func(start_cmd, index, flag))
			return (0);
	return (1);
}