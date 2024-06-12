#include "minishell.h"

int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = 0;
	while (*line)
	{
		if (tokkened)
			if (ft_isin_table(*line, "<>|"))
				return (fprintf(stderr, "minishell: errror near unexpected tokken \'%c\'\n", *line), 0);
		if (*line != ' ')
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

int	all_good(char *line)
{
	t_stof	*stofs;
	int		index;

	stofs = str_to_func();
	index = 0;
	if (!verif_tokken(line))
		return (0);
	while (line[index])
	{
		if (line[index] == '>' || line[index] == '<')
			if (!redirects(&line, &index, stofs, 0))
				return (free(stofs), free(line), 0);
		if (line[index] != '\0')
			index++;
	}
	(free(stofs), free(line));
	return (1);
}
