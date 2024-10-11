/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:57:40 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/11 15:17:45 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_hdoc_only_case(t_cmd *cmd, char **line)
{
	char	tmp;
	char	*str;

	str = cmd->cmd;
	while (*str)
		if (!ft_iswhitespace(*str++))
			return (0);
	while (read(cmd->in, &tmp, 1) == -1 || tmp != '\0')
	{
		if (write(cmd->out, &tmp, 1) == -1)
		{
			(close(cmd->in), close(cmd->out), free(cmd->cmd));
			*line = NULL;
			return (1);
		}
	}
	(close(cmd->in), close(cmd->out));
	return (1);
}

char	*cmd_redirects(t_list *cmd)
{
	char	*str;

	str = ((t_cmd *)(cmd->content))->cmd;
	if (((t_cmd *)(cmd->content))->here_doc && ((t_cmd *)(cmd->content))->out)
		if (cmd_hdoc_only_case(cmd->content, &str))
			return (free(cmd->content), free(cmd), str);
	if (((t_cmd *)(cmd->content))->in
		&& dup2(((t_cmd *)(cmd->content))->in, STDIN_FILENO) == -1)
		return (perror("dup2 "), free_cmd(cmd), NULL);
	if (((t_cmd *)(cmd->content))->out
		&& dup2(((t_cmd *)(cmd->content))->out, STDOUT_FILENO) == -1)
		return (perror("dup2"), free_cmd(cmd), NULL);
	if (((t_cmd *)(cmd->content))->in)
		close(((t_cmd *)(cmd->content))->in);
	if (((t_cmd *)(cmd->content))->out)
		close(((t_cmd *)(cmd->content))->out);
	return (free(cmd->content), free(cmd), str);
}
