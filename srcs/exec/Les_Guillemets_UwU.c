#include "../../includes/minishell.h"

char	*tatu_ferme_tes_guillemets(char *str);

char	*bah_ferme_les(char *str)
{
	char	*one;
	char	*another_one;
	char	*and_another_one;

	if (!gere_sig(GUILLEMETS))
		return (NULL);//free peuit etre aussi ?
	//fprintf(stderr, "mhhh I see I see\n");
	rl_getc_function = getc;
	one = readline("> ");
	rl_getc_function = rl_getc;
	if (!one)
		return (add_history(str), fprintf(stderr, "unexpected EOF while lookink for matching `\'\'\n syntax error unexpected end of file\n"), NULL);
	if (!gere_sig(READING_LINE))
		return (0);
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
	while (*itterand && (ft_iswhitespace(*itterand) || *itterand == '\n'))
		itterand++;
	if (*itterand == '\0')
		return (bah_ferme_les(str));
	if (ft_isin_table(*itterand, "|<>;"))//maybe more
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

	if (!str)
	  	return (NULL);
	voyage = str;
	while (*voyage)
	{
		pipe_good = et_le_pipe(str, voyage);
		if (pipe_good != str)
			return (pipe_good);
		if (*voyage == '\"' || *voyage == '\'')
		{
			//printf("voici la ligne awawawaw : %s  : %s\n", str, voyage);
			this_one = *voyage++;
			while (*(voyage + 1) != '\0' && *voyage != this_one)
				voyage++;
			if (*voyage != this_one)
				return (bah_ferme_les(str));
		}
		voyage++;
	}
	add_history(str);//Ca pourrais etre bien de faire en sorte que les lignes vides et les lignes remplis que de uspace ne soit pas mis dans l'historique.
	//ca prends pas le here doc en compte.... ca fait chier un peu....
	return (str);
}
