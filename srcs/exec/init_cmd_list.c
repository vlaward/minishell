#include "../../includes/minitest.h"

void	fill_cmd(t_cmd *cmd, int in, int out, int childs_bool)
{
	cmd->in = in;
	cmd->out = out;
	cmd->childs_bool = childs_bool;
}

t_cmd	*cmd_dup(t_cmd cmd)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ret->cmd = cmd.cmd;
	ret->in = cmd.in;
	ret->out = cmd.out;
	return (ret);
}

void	free_cmd(void *afree)
{
	if (!afree)
		return ;
	free(((t_cmd *)afree)->cmd);
	free(afree);
}

t_list	*piped_node(t_cmd *cmd, char *line, int *index, int *start_cmd)
{
	t_cmd	tmp;

	cmd->childs_bool = 1;
	line[(*index)++] = '\0';
	cmd->cmd = ft_strdup(&(line[(*start_cmd)]));
	*start_cmd = *index;
	tmp = *cmd;
	cmd->in = 0;
	cmd->out = 0;
	return (ft_lstnew(cmd_dup(tmp)));
}

t_list	*init_cmd(char *line, t_list *env)
{
	int		index;
	int		start_cmd;
	t_list	*ret;
	t_cmd	tmp;

	if (!verif_tokken(line))
		return (0);
	index = -1;
	start_cmd = 0;
	ret = NULL;
	fill_cmd(&tmp, 0 ,0 ,0);
	while (line[++index])
	{
		if (line[index] == '>' || line[index] == '<')
			if (!redirects(&line, &index, &tmp, env))
				return (free(line), ft_lstclear(&ret, free_cmd), NULL);
		if (line[index] == '|')
			if (!ft_lstadd_front(&ret, piped_node(&tmp, line, &index, &start_cmd)))
				return (perror("malloc"), free(line), ft_lstclear(&ret, free_cmd), NULL);
	}
	tmp.cmd = ft_strdup(&(line[start_cmd]));
	start_cmd = index;
	ft_lstadd_front(&ret, ft_lstnew(cmd_dup(tmp)));
	free(line);
	return (ret);
}
