/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Les_Guillemets_UwU.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:12:59 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/12 16:12:31 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	passe_les_guillemets(char *str, int i)
{
	char	tmp;

	if (str[i] != '\"' && str[i] != '\'')
		return (i);
	tmp = str[i++];
	while (str[i] && str[i] != tmp)
		i++;
	if (str[i])
		i++;
	return (i);
}

char	*tatu_ferme_tes_guillemets(char *str, t_list *env);

char	*second_readline(char *str)
{
	char	*red;

	red = NULL;
	if (!gere_sig(GUILLEMETS))
		return (NULL);
	rl_getc_function = getc;
	red = readline(str);
	rl_getc_function = rl_getc;
	if (!gere_sig(READING_LINE))
		return (free(red), NULL);
	return (red);
}

char	*bah_ferme_les(char *str, t_list *env)
{
	char	*one;
	char	*another_one;
	char	*and_another_one;

	one = second_readline(">");
	if (!one)
	{
		if (g_sig_catcher != SIGINT)
			return (add_history(str), guille_error(), NULL);
		return (add_history(str), NULL);
	}
	another_one = ft_strjoin(str, "\n");
	if (!another_one)
		return (free(one), NULL);
	and_another_one = ft_strjoin(another_one, one);
	(free(one), free(another_one), free(str));
	return (tatu_ferme_tes_guillemets(and_another_one, env));
}

char	*et_le_pipe(char *str, char *itterand, t_list *env)
{
	if (*itterand != '|')
		return (str);
	itterand++;
	while (*itterand && (ft_iswhitespace(*itterand) || *itterand == '\n'))
		itterand++;
	if (*itterand == '\0')
		return (bah_ferme_les(str, env));
	if (*itterand == '|')
	{
		add_history(str);
		return (syntax_error(itterand), free(str), NULL);
	}
	return (str);
}

char	*tatu_ferme_tes_guillemets(char *str, t_list *env)
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
		pipe_good = et_le_pipe(str, voyage, env);
		if (pipe_good != str)
			return (pipe_good);
		if (*voyage == '\"' || *voyage == '\'')
		{
			this_one = *voyage++;
			while (*voyage && *(voyage + 1) != 0 && *voyage != this_one)
				voyage++;
			if (*voyage != this_one)
				return (bah_ferme_les(str, env));
		}
		voyage++;
	}
	return (add_history(str), str);
}
