#include "../../includes/minitest.h"

static void	fill_cmd(t_cmd *cmd, int in, int out, int has_pipe)
{
	cmd->in = in;
	cmd->out = out;
	cmd->has_pipe = has_pipe;
}

static t_cmd	*cmd_dup(t_cmd cmd)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->cmd = cmd.cmd;
	ret->in = cmd.in;
	ret->out = cmd.out;
	ret->has_pipe = cmd.has_pipe;
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
	cmd->in = 0;
	cmd->out = 0;
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
		return (0);
	index = 0;
	ret = NULL;
	fill_cmd(&tmp, 0 ,0 ,0);
	printf("Voici the FUCKING LINE : \'%s\'\n", line);
	while (line[index])
	{
		if (line[index] == '>' || line[index] == '<')
		{
			if (!redirects(&line, &index, &tmp, env))
				return (free(line), ft_lstclear(&ret, free_cmd), NULL);
		}
		else if (line[index] == '|')
		{
			if (!ft_lstadd_front(&ret, piped_node(&tmp, &line, &index)))
				return (perror("malloc"), free(line), ft_lstclear(&ret, free_cmd), NULL);
		}
		else
			index++;
		printf("Voici the FUCKING LINE : \'%s\'\n", line);
		printf("%u\n", index);
	}
	tmp.cmd = ft_strdup(line);
	if (!tmp.cmd)
		return (perror("malloc"), free(line), ft_lstclear(&ret, free_cmd), NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew_content_mandatory(cmd_dup(tmp))))
		return (perror("malloc"), free(line), ft_lstclear(&ret, free_cmd), NULL);
	return (free(line), ret);
}
