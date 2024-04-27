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

char	*tatu_ferme_tes_guillemets(char *str)
{
	char	*voyage;
	char	this_one;

	voyage = str;
	while (*voyage)
	{
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
