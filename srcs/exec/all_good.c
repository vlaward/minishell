/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_good.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:31:14 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/11 13:12:16 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verif_tokken(char *line)
{
	int		tokkened;
	char	tmp;

	tokkened = 0;
	tmp = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			tmp = *line++;
		if (tmp == '\'' || tmp == '\"')
			while (*line && *line != tmp)
				line++;
		else if (tokkened)
			if (ft_isin_table(*line, "<>|")
				&& !(*line != '|' && tokkened == '|'))
				return (syntax_error(line), 0);
		if (!ft_iswhitespace(*line))
			tokkened = ft_isin_table(*line, "<>|") * *line;
		if (*line && *(line + 1) == *line && (*line == '>' || *line == '<'))
			line++;
		line += (*line != '\0');
	}
	if (tokkened && tokkened != '|')
		return (syntax_error(NULL), 0);
	return (1);
}

