#include "../../includes/minishell.h"

int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = 0;
	while (*line)
	{
		if (tokkened)
			if (ft_isin_table(*line, "<>|"))
				return (fprintf(stderr, "minishell: errror near unexpected tokken \'%c\'\n", *line), 0);
		if (!ft_iswhitespace(*line))
			tokkened = ft_isin_table(*line, "<>|");
		if (tokkened)
			tokkened = (int)*line;
		if (*(line + 1) == *line && (*line == '>' || *line == '<'))
			line++;
		line++;
	}
	if (tokkened && tokkened != '|')
		return (fprintf(stderr, "minishell: errror near unexpected tokken 'newline'\n"),  0);
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
				return (free(line), printf("c'est donc ici que le probleme est\n"), 0);
		if (line[index] != '\0')
			index++;
	}
	free(line);
	return (1);
}
