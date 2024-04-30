#include "minishell.h"

char	*tatu_ferme_tes_guillemets(char *str);

char	*bah_ferme_les(char *str)
{
	char	*one;
	char	*another_one;
	char	*and_another_one;

	one = readline("> ");
	another_one = ft_strjoin(str, "\n");
	and_another_one = ft_strjoin(another_one, one);
	(free(one), free(another_one), free(str));
	return (tatu_ferme_tes_guillemets(and_another_one));
}

char	*et_le_pipe(char *str, char *itterand)
{
	if (*itterand != '|')
		return (str);
	itterand++;
	while (*itterand && *itterand == ' ')
		itterand++;
	if (*itterand == '\0')
		return(bah_ferme_les(str));
	if (ft_isin_table(*itterand, "|<>;|"))//maybe more
	{
		add_history(str);
		return(fprintf(stderr, "syntax error near unexpected token \'%c\'\n", *str), free(str), NULL);
	}
	return (str);
}

char	*tatu_ferme_tes_guillemets(char *str)
{
	char	*voyage;
	char	this_one;
	char	*pipe_good;

	voyage = str;
	while (*voyage)
	{
		pipe_good = et_le_pipe(str, voyage);
		if (pipe_good != str)
			return (pipe_good);
		if (*voyage == '\"' || *voyage == '\'')
		{
			this_one = *voyage++;
			while (*voyage && *voyage != this_one)
				voyage++;
			if (*voyage == '\0')
				return (bah_ferme_les(str));
		}
		voyage++;
	}
	return (str);
}
