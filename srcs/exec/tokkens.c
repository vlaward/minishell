/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokkens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:39:58 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 18:27:37 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_handler(char **start_cmd, int *i, t_list *env)
{
	int		j;
	char	*env_value;
	char	*tmp;

	j = *i;
	while ((*start_cmd)[++j] && !ft_isin_table((*start_cmd)[j], " <>|$\'\""))
		(*start_cmd)[j - 1] = (*start_cmd)[j];
	if (j == *i + 1)
		return (++(*i));
	(*start_cmd)[j - 1] = '\0';
	env_value = ft_getenv(&(*start_cmd)[*i], env);
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(env_value, &((*start_cmd)[j]));
	if (!tmp)
		return (-1);
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	if (env_value == NULL || *start_cmd == NULL)
		return (-1);
	*i += ft_strlen(env_value) - 1;
	return (*i);
}

int	guille_handler(char **start_cmd, int *i, int flag, t_list *env)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while ((*start_cmd)[j] && (*start_cmd)[j] != (*start_cmd)[*i])
	{
		if (flag != H_DOC_TRIM
			&& (*start_cmd)[*i] == '\"' && (*start_cmd)[j] == '$')
			if (env_handler(start_cmd, &j, env) == -1 && flag == F_NAME_TRIM)
				return (-1);
		if ((*start_cmd)[j] != '\0')
			j++;
	}
	(*start_cmd)[j] = '\0';
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(&(*start_cmd)[*i + 1], &(*start_cmd)[j + 1]);
	if (!tmp)
		return (-1);
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	if (!*start_cmd)
		return (-1);
	*i = j - 1;
	return (j - 1);
}

char	*trim(char **cmd, int *index, int flag, t_list *env)
{
	int		start_index;
	int		start_name_index;

	start_index = *index;
	*index += 1 + ((*cmd)[*index] == (*cmd)[*index + 1]);
	while (ft_iswhitespace((*cmd)[*index]))
		*index += 1;
	start_name_index = *index;
	while ((*cmd)[*index] != '\0' && !ft_iswhitespace((*cmd)[*index]))
	{
		if ((*cmd)[*index] == '\'' || (*cmd)[*index] == '\"')
			*index = guille_handler(cmd, index, flag, env);
		else if (ft_isin_table((*cmd)[*index], "<>|"))
			break ;
		else if (flag != H_DOC_TRIM && (*cmd)[*index] == '$')
			*index = env_handler(cmd, index, env);
		else
			*index += 1;
		if (*index == -1 && big_error())
			return (NULL);
		if (*index == -1)
			return (ft_putestr_fd("Ambiguous redirects\n", STDERR_FILENO), "F");
	}
	(*cmd)[start_index] = '\0';
	return (ft_strndup(&(*cmd)[start_name_index], *index - start_name_index));
}
