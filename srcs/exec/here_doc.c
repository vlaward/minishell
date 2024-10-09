/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:26:56 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 12:39:09 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define SYNTAX_ERR_NL "syntax error near unexpecterd token \'newline\'"

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
	while (*red && (*red)[i] != '\0')
	{
		if ((*red)[i] == '$')
			i = env_handler(red, &i, env);
		else
			i++;
		if (i < 0)
			return (free(red), 0);
	}
	if (!*red)
		return (0);
	return (1);
}

char	*read_doc(char *limitter, t_list *env)
{
	char	*red;
	char	*here_doc;

	red = NULL;
	here_doc = NULL;
	while (1)
	{
		red = readline("here_doc >");
		if (!here_doc_env(&red, env))
			return (free(here_doc), free(limitter), NULL);
		if (ft_strcmp(limitter, red) == 0)
			break ;
		here_doc = ft_strjoin_n_free(here_doc, ft_strjoin(red, "\n"));
		if (!here_doc)
			return (perror("malloc"), NULL);
		free(red);
	}
	free(red);
	return (here_doc);
}

int	here_doc(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	char	*limitter;
	char	*tmp_cmd;
	int		start_index;
	char	*here_doc;

	start_index = *index;
	limitter = trim(start_cmd, index, H_DOC_TRIM, env);
	if (limitter == NULL)
	{
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd(SYNTAX_ERR_NL, STDERR_FILENO);
		return (0);
	}
	here_doc = read_doc(limitter, env);
	if (!here_doc)
		return (free(limitter), 0);
	cmd->in = write_here(here_doc);
	tmp_cmd = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp_cmd)
		return (free(limitter), 0);
	(free(limitter), free(*start_cmd));
	*start_cmd = tmp_cmd;
	*index = start_index;
	return (1);
}
