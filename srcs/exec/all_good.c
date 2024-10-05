/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_good.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:31:14 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/05 06:46:12 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = 0;
	while (*line)
	{
		if (tokkened)
			if (ft_isin_table(*line, "<>|")
				&& !(*line != '|' && tokkened == '|'))
				return (fprintf(stderr
						, "minishell: errror near unexpected tokken \'%c\'\n"
						, *line), 0);
		if (!ft_iswhitespace(*line))
			tokkened = ft_isin_table(*line, "<>|") * *line;
		if (*(line + 1) == *line && (*line == '>' || *line == '<'))
			line++;
		line++;
	}
	if (tokkened && tokkened != '|')
		return (fprintf(stderr
				, "minishell: errror near unexpected tokken 'newline'\n"), 0);
	return (1);
}

int	all_good(char *line, t_list *env)
{
	int		index;

	index = 0;
	if (!verif_tokken(line))
		return (0);
	while (line[index])
	{
		if (line[index] == '>' || line[index] == '<')
			if (!redirects(&line, &index, 0, env))
				return (free(line), 0);
		if (line[index] != '\0')
			index++;
	}
	free(line);
	return (1);
}
