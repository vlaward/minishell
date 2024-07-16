#include "../../includes/minitest.h"


int	write_here(char *towrite)
{
	int	pipette[2];
	int	ret;

	if (pipe(pipette) == -1)
		return (free(towrite), perror("pipe"), 0);
	ret = dup(pipette[0]);
	if (ret == -1)
		return (free(towrite), perror("dup"), 0);
	ft_putestr_fd(towrite, pipette[1]);
	close(pipette[0]);
	close(pipette[1]);
	free(towrite);
	return (ret);
}

int	here_doc_env(char **red, t_list *env)
{
	int	i;

	if (!(*red))
		return (0);
	i = 0;
	while ((*red)[i] != '\0')
	{
		if ((*red)[i] == '$')
			i = env_handler(red, &i, env);
		else
			i++;
		if (i < 0)		
			return (0);
	}
	return (1);
}

int	here_doc(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	char	*limitter;
	char	*red;
	char	*here_doc;
	char	*tmp_cmd;
	int		start_index;

	//fprintf(stderr, "voici voila : %s\n", *start_cmd);
	(*start_cmd)[*index] = '\0';
	start_index = *index;
	*index += 1;
	limitter = trim(start_cmd, index, H_DOC_TRIM, env);
	if (limitter == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd("syntax error near unexpecterd token \'newline\'", STDERR_FILENO);
		//fprintf(stderr, "soit c'est ca mais c'est pas logique\n");
		return (0);
	}
	red = NULL;
	here_doc = NULL;
	while (1)
	{
		red = readline("here_doc >");
		if (!here_doc_env(&red, env))
			return (perror("readline"), free(here_doc), free(limitter), 0);
		if (ft_strcmp(limitter, red) == 0)
			break;
		here_doc = ft_strjoin_n_free(here_doc, ft_strjoin(red, "\n"));
		if (!here_doc)
			return (ft_putestr_fd("don't know\n", STDERR_FILENO), 0);
		free(red);
	}
	cmd->in = write_here(here_doc);
	tmp_cmd = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	(free(red), free(limitter), free(*start_cmd));
	*start_cmd = tmp_cmd;
	*index = start_index	;
	return (1);
}