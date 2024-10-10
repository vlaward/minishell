/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:26:56 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/10 17:03:42 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define SYNTAX_ERR_NL "syntax error near unexpecterd token \'newline\'"

int	write_here(char *towrite, t_cmd *cmd)
{
	int	pipette[2];
	int	ret;

	if (cmd->in && close(cmd->in) == -1)
		return (0);
	if (pipe(pipette) == -1)
		return (free(towrite), perror("pipe"), 0);
	ret = dup(pipette[0]);
	if (ret == -1)
		return (free(towrite), perror("dup"), 0);
	if (ft_putestr_fd(towrite, pipette[1]) == -1)
		return (free(towrite), 0);
	if (ft_putechar_fd('\0', pipette[1]) == -1)
		return (free(towrite), 0);
	free(towrite);
	if (close(pipette[0]) == -1 || close(pipette[1]) == -1)
		return (0);
	return (ret);
}

int	here_doc_env(char **red, t_list *env)
{
	int	i;

	if (!red || !(*red))
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

char	*read_doc(char *limitter, t_list *env, t_cmd *cmd)
{
	char	*red;
	char	*here_doc;

	red = NULL;
	here_doc = NULL;
	while (1 && cmd->here_doc_number <= 16)
	{
		red = second_readline("here_doc >");
		if (!red)
		{
			if (g_sig_catcher != SIGINT)
				ft_putestr_fd("bash : warning : here-doc delimited by EOF\n",
					STDERR_FILENO);
			return (free(here_doc), NULL);
		}
		if (ft_strcmp(limitter, red) == 0)
			break ;
		if (!here_doc_env(&red, env))
			return (free(here_doc), NULL);
		here_doc = ft_strjoin_n_free(here_doc, ft_strjoin(red, "\n"));
		free(red);
		if (!here_doc)
			return (perror("malloc"), NULL);
	}
	return (free(red), here_doc);
}

int	here_doc(char **start_cmd, int *index, t_cmd *cmd, t_list *env)
{
	char	*limit;
	char	*tmp_cmd;
	int		start_index;
	char	*here_doc;

	start_index = *index;
	limit = trim(start_cmd, index, H_DOC_TRIM, env);
	if (limit == NULL)
		if (!ft_iswhitespace((*start_cmd)[*index]))
			ft_putestr_fd(SYNTAX_ERR_NL, STDERR_FILENO);
	if (limit == NULL)
		return (0);
	here_doc = read_doc(limit, env, cmd);
	if (!here_doc)
		return (free(limit), 0);
	cmd->in = write_here(here_doc, cmd);
	if (cmd->in == 0)
		return (free(limit), free(here_doc), 0);
	tmp_cmd = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	if (!tmp_cmd)
		return (free(limit), 0);
	(free(limit), free(*start_cmd));
	*start_cmd = tmp_cmd;
	*index = start_index;
	return (1);
}
