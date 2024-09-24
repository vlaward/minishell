#include "../../includes/minitest.h"

//verifier si errno est bien a 0 a la base
int	in_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM, env);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (fprintf(stderr, "donc clairement c'est ici\n"), 0);
	}
	if (cmd->in != 0)
		close(cmd->in);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return(perror("open"), free(file), 0);
	cmd->in = fd;//.je pense qu'il y a pas besoin de ca
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;
	return (free(file), tmp != NULL);
}

int	append_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM, env);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (fprintf(stderr, "donc clairement c'est ici\n"), 0);
	}
	if (cmd->out != 0)
		close(cmd->out);
	fd = open(file, O_RDWR| O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
	if (fd == -1)
		return(perror("open"), 0);
	cmd->out = fd;//.je pense qu'il y a pas besoin de ca
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;
	return (free(file), tmp != NULL);
}

int	out_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM, env);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("there aint no file bud ;-;\n", STDERR_FILENO);
		return (fprintf(stderr, "donc clairement c'est ici\n"), 0);
	}
	if (cmd->out != 0)
		close(cmd->out);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
	if (fd == -1)
		return(perror("open"), 0);
	cmd->out = fd;//.je pense qu'il y a pas besoin de ca
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 2;
	free(*start_cmd);
	*start_cmd = tmp;
	return (free(file), tmp != NULL);
}

int	redirects(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	fprintf(stderr, "ça passe ti pars la ?");
	if ( ft_strncmp(&(*start_cmd)[*index], ">>", 2) == 0)
		return(append_handler(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], "<<", 2) == 0)
		return(here_doc(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], "<", 1) == 0)
		return(in_handler(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], ">", 1) == 0)
		return(out_handler(start_cmd, index, cmd, env));
	return (printf("LA ?????"), 0);
}
/*
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
}*/
