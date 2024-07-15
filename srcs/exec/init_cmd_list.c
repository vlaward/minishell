#include "../../includes/minitest.h"

int	outest_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
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


/*int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = 0;
	while (*line)
	{
		if (tokkened)
			if (ft_isin_table(*line, "<>|"))
				return (fprintf(stderr, "minishell: errror near unexpected tokken \'%c\'\n", *line), 0);
		if (!ft_iswhitespace(*line))
			tokkened = ft_isin_table(*line, "<>|");
		if (*(line + 1) == *line && (*line == '>' || *line == '<'))
			line++;
		line++;
	}
	if (tokkened && tokkened != '|')
		return (fprintf(stderr, "minishell: errror near unexpected tokken 'newline'\n"),  0);
	return (1);
}*/

t_cmd	*cmd_dup(t_cmd cmd)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ret->cmd = cmd.cmd;
	ret->in = cmd.in;
	ret->out = cmd.out;
	return (ret);
}

t_list	*init_cmd(char *line, t_list *env)
{
	int		index;
	int		start_cmd;
	t_list	*ret;
	t_cmd	tmp;

	if (!verif_tokken(line))
		return (0);
	index = 0;
	ret = ft_lstnew(NULL);
	start_cmd = 0;
	tmp.in = 0;
	tmp.out = 0;
	while (line[index])
	{
		if (line[index] == '>' || line[index] == '<')
			if (!outest_handler(&line, &index, &tmp, env))
				return (free(line), printf("c'est donc ici que le probleme est\n"), NULL);
		if (line[index] == '|')
		{
			line[index++] = '\0';
			tmp.cmd = ft_strdup(&(line[start_cmd]));
			start_cmd = index;
			ft_lstadd_front(&ret, ft_lstnew(cmd_dup(tmp)));
			tmp.in = 0;
			tmp.out = 0;
			
		}
		if (line[index] != '\0')
			index++;
	}
	tmp.cmd = ft_strdup(&(line[start_cmd]));
	start_cmd = index;
	ft_lstadd_front(&ret, ft_lstnew(cmd_dup(tmp)));
	free(line);
	return (ret);
}
