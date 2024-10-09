/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:40:57 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 18:27:37 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//verifier si errno est bien a 0 a la base
int	in_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = trim(start_cmd, index, F_NAME_TRIM, env);
	if ((file == NULL && errno != 0) || (file && !ft_strcmp(file, "F")))
		return (0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n"
				, STDERR_FILENO), 0);
	if (cmd->in != 0)
		if (close(cmd->in) == -1)
			return (free(file), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), free(file), 0);
	cmd->in = fd;
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
	if ((file == NULL && errno != 0) || (file && !ft_strcmp(file, "F")))
		return (0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n"
				, STDERR_FILENO), 0);
	if (cmd->out != 0)
		if (close(cmd->out) == -1)
			return (free(file), 0);
	fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (perror("open"), free(file), 0);
	cmd->out = fd;
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
	if ((file == NULL && errno != 0) || (file && !ft_strcmp(file, "F")))
		return (0);
	if (file == NULL)
		return (ft_putestr_fd(": : No such file or directory\n"
				, STDERR_FILENO), 0);
	if (cmd->out != 0)
		if (close(cmd->out) == -1)
			return (free(file), 0);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (perror("open"), free(file), 0);
	cmd->out = fd;
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
	if (ft_strncmp(&(*start_cmd)[*index], ">>", 2) == 0)
		return (append_handler(start_cmd, index, cmd, env));
	if (ft_strncmp(&(*start_cmd)[*index], "<<", 2) == 0)
		return (here_doc(start_cmd, index, cmd, env));
	if (ft_strncmp(&(*start_cmd)[*index], "<", 1) == 0)
		return (in_handler(start_cmd, index, cmd, env));
	if (ft_strncmp(&(*start_cmd)[*index], ">", 1) == 0)
		return (out_handler(start_cmd, index, cmd, env));
	return (0);
}

int	init_redirects(t_list *cmd, t_list *env)
{
	int	i;
	int	error;

	while (cmd)
	{
		error = 0;
		i = -1;
		while (cmd && ((t_cmd *)(cmd->content))->cmd && !error
			&& ((t_cmd *)(cmd->content))->cmd[++i])
		{
			if (ft_isin_table(((t_cmd *)(cmd->content))->cmd[i], "><"))
				if (!redirects(&((t_cmd *)(cmd->content))->cmd
					, &i, (t_cmd *)(cmd->content), env))
					error = 1;
			if (((t_cmd *)(cmd->content))->cmd)
				((t_cmd *)(cmd->content))->cmd[0] *= !error;
			if (error || !((t_cmd *)(cmd->content))->cmd[i])
				break ;
		}
		if (big_error())
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
