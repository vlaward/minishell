/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Les_Guillemets_UwU.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:12:59 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/09 10:48:15 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tatu_ferme_tes_guillemets(char *str);

char	*bah_ferme_les(char *str)
{
	char	*one;
	char	*another_one;
	char	*and_another_one;

	if (!gere_sig(GUILLEMETS))
		return (NULL);
	rl_getc_function = getc;
	one = readline("> ");
	rl_getc_function = rl_getc;
	if (!one)
		return (add_history(str), fprintf(stderr, "unexpected EOF while lookink for matching `\'\'\n syntax error unexpected end of file\n"), NULL);
	if (!gere_sig(READING_LINE))
		return (NULL);
	another_one = ft_strjoin(str, "\n");
	if (!another_one)
		return (free(one), NULL);
	and_another_one = ft_strjoin(another_one, one);
	(free(one), free(another_one), free(str));
	return (tatu_ferme_tes_guillemets(and_another_one));
}

char	*et_le_pipe(char *str, char *itterand)
{
	if (*itterand != '|')
		return (str);
	itterand++;
	while (*itterand && (ft_iswhitespace(*itterand) || *itterand == '\n'))
		itterand++;
	if (*itterand == '\0')
		return (bah_ferme_les(str));
	if (ft_isin_table(*itterand, "|"))
	{
		add_history(str);
		return (fprintf(stderr, "syntax error near unexpected token \'|\'\n"), free(str), NULL);
	}
	return (str);
}

char	*tatu_ferme_tes_guillemets(char *str)
{
	char	*voyage;
	char	this_one;
	char	*pipe_good;

	if (!str)
		return (NULL);
	if (!*str)
		return (free(str), NULL);
	voyage = str;
	while (*voyage)
	{
		pipe_good = et_le_pipe(str, voyage);
		if (pipe_good != str)
			return (pipe_good);
		if (*voyage == '\"' || *voyage == '\'')
		{
			this_one = *voyage++;
			while (*voyage && *(voyage + 1) != 0 && *voyage != this_one)
				voyage++;
			if (*voyage != this_one)
				return (bah_ferme_les(str));
		}
		voyage++;
	}
	return (add_history(str), str);
}
