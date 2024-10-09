/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:06:20 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/09 11:34:23 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	increment_atl(char **str, int *i, t_list *env, char witch)
{
	if (ft_isin_table((*str)[*i], "\'\""))
	{
		witch = (*str)[*i];
		ft_memcpy(&((*str)[*i]), &(*str)[*i + 1], ft_strlen(&(*str)[*i + 1]));
		(*str)[ft_strlen(*str) - 1] = '\0';
		while ((*str)[*i] && (*str)[*i] != witch)
		{
			if ((*str)[*i] != '$' || ((*str)[*i] == '$' && witch == '\''))
				(*i)++;
			else
				if (env_handler(str, i, env) == -1)
					return (0);
		}
		if ((*str)[*i])
			ft_memcpy(&((*str)[*i]), &(*str)[*i + 1],
				ft_strlen(&(*str)[*i + 1]));
		(*str)[*i + ft_strlen(&((*str)[*i])) - 1] = '\0';
	}
	else if ((*str)[*i] != '$')
		(*i)++;
	else
		if (env_handler(str, i, env) == -1)
			return (0);
	return (1);
}

static int	add_to_list(char **line, int *index, t_list *env, t_list **wbr)
{
	int		i;
	char	*content;
	char	*str;
	char	witch;

	witch = '\0';
	i = *index;
	str = *line;
	while (str[i] && !ft_iswhitespace(str[i]) && str[i] != '\n')
		if (!increment_atl(&str, &i, env, witch))
			return (0);
	*line = str;
	content = ft_strndup(&str[*index], i - *index);
	if (i - *index == 0)
		content = ft_strdup("\0");
	if (!content)
		return (0);
	*index = i - 1;
	return (ft_lstadd_front(wbr, ft_lstnew(content)));
}

char	**ft_minisplit(char	*str, t_list *env)
{
	t_list	*will_be_ret;
	int		i;
	char	**ret;

	if (!str)
		return (NULL);
	will_be_ret = NULL;
	i = -1;
	while ((str)[++i])
		if (!ft_iswhitespace((str)[i]) && (str)[i] != '\n')
			if (!add_to_list(&str, &i, env, &will_be_ret))
				return (free(str), perror("malloc"), NULL);
	if (!will_be_ret)
		return (free(str), NULL);
	ret = ft_calloc(ft_lstsize(will_be_ret) + 1, sizeof(char *));
	if (!ret)
		return (free(str), perror("malloc"), NULL);
	i = -1;
	while (ft_lstnodi(&will_be_ret, ++i))
		ret[i] = ft_lstnodi(&will_be_ret, i)->content;
	ft_lstclear(&will_be_ret, NULL);
	free(str);
	return (ret);
}
