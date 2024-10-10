/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:17:49 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/10 18:26:39 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_cmd(t_cmd *cmd, int in, int out, int has_pipe)
{
	cmd->in = in;
	cmd->out = out;
	cmd->has_pipe = has_pipe;
}

static t_cmd	*cmd_dup(t_cmd cmd)
{
	t_cmd	*ret;

	if (!cmd.cmd)
		return (NULL);
	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->cmd = cmd.cmd;
	ret->in = cmd.in;
	ret->out = cmd.out;
	ret->has_pipe = cmd.has_pipe;
	ret->here_doc = 0;
	ret->here_doc_number = 0;
	return (ret);
}

void	free_cmd(void *afree)
{
	if (!afree)
		return ;
	if (((t_cmd *)afree)->in > 3)
		close(((t_cmd *)afree)->in);
	if (((t_cmd *)afree)->out > 3)
		close(((t_cmd *)afree)->out);
	if (((t_cmd *)afree)->cmd != NULL)
		free(((t_cmd *)afree)->cmd);
	free(afree);
}

static t_list	*piped_node(t_cmd *cmd, char **line, int *index)
{
	t_cmd	tmp;
	char	*new_line;

	(*line)[(*index)++] = '\0';
	new_line = ft_strdup(&(*line)[*index]);
	if (!new_line)
		return (NULL);
	cmd->cmd = ft_strdup(*line);
	if (!cmd->cmd)
		return (NULL);
	cmd->has_pipe = 1;
	tmp = *cmd;
	free(*line);
	*line = new_line;
	*index = 0;
	return (ft_lstnew_content_mandatory(cmd_dup(tmp)));
}

t_list	*init_cmd(char *line, t_list *env)
{
	int		index;
	t_list	*ret;
	t_cmd	tmp;

	if (!verif_tokken(line))
		return (NULL);
	index = 0;
	ret = NULL;
	fill_cmd(&tmp, 0, 0, 0);
	while (line[index])
	{
		index = passe_les_guillemets(line, index);
		if (line[index] && line[index] != '|')
			index++;
		else if (line[index])
			if (!ft_lstadd_front(&ret, piped_node(&tmp, &line, &index)))
				return (perror("malloc"), free(line)
					, ft_lstclear(&ret, free_cmd), NULL);
	}
	tmp.cmd = ft_strdup(line);
	free(line);
	if (!ft_lstadd_front(&ret, ft_lstnew_content_mandatory(cmd_dup(tmp)))
		|| !init_redirects(ret, env))
		return (perror("malloc"), ft_lstclear(&ret, free_cmd), NULL);
	return (ret);
}
