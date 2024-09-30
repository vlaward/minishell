#include "../../includes/minitest.h"

//verifier si errno est bien a 0 a la base
int	in_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM, env);
	// fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
		if (errno != 0)
			return (fprintf(stderr, "donc clairement c'est ici\n"), perror("test:"), 0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n", STDERR_FILENO), 0);
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

	(*start_cmd)[(*index)++] = '\0';
	file = trim(start_cmd, index, F_NAME_TRIM, env);
	// fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
		if (errno != 0)
			return (fprintf(stderr, "donc clairement c'est ici\n"), perror("test:"), 0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n", STDERR_FILENO), 0);
	if (cmd->out != 0)
		close(cmd->out);
	fd = open(file, O_RDWR| O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return(perror("open"), free(file), 0);
	cmd->out = fd;//.je pense qu'il y a pas besoin de ca
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp && errno != 0)
		return (perror("malloc"), 0);
	*index -= ft_strlen(file) + 3;
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
	// fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
		if (errno != 0)
			return (fprintf(stderr, "donc clairement c'est ici\n"), perror("test:"), 0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n", STDERR_FILENO), 0);
	if (cmd->out != 0)
		close(cmd->out);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return(perror("open"), free(file), 0);
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
	if ( ft_strncmp(&(*start_cmd)[*index], ">>", 2) == 0)
		return(append_handler(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], "<<", 2) == 0)
		return(here_doc(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], "<", 1) == 0)
		return(in_handler(start_cmd, index, cmd, env));
	if ( ft_strncmp(&(*start_cmd)[*index], ">", 1) == 0)
		return(out_handler(start_cmd, index, cmd, env));
	return (0);
}

void	init_redirects(t_list *cmd, t_list *env)
{
	int	i;
	int	error;
	int	tmp;
	
	error = 0;
	tmp = error;
	while (cmd)
	{
		i = 0;
		while (((t_cmd*)(cmd->content))->cmd && error == tmp
			&& ((t_cmd*)(cmd->content))->cmd[i])
		{
			if (!ft_isin_table(((t_cmd*)(cmd->content))->cmd[i], "><"))
				i++;
			else
				if (!redirects(&((t_cmd*)(cmd->content))->cmd, &i, (t_cmd*)(cmd->content), env))
					error++;
			if (error != tmp)
				((t_cmd*)(cmd->content))->cmd[0] = '\0';
			if (error != tmp)
				break ;
		}
		tmp = error;
		cmd = cmd->next;
	}
}

