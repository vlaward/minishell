#include "minishell.h"
#define TRIME_NAME 1
#define ADD_ENV 0

int		guille_handler(char **start_cmd, int *i)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while ((*start_cmd)[j] != (*start_cmd)[*i])
	{
		if ((*start_cmd)[*i] == '\"' && (*start_cmd)[j] == '$')
			if (env_handler(start_cmd, i) == -1)
				return (-1);
		j++;
	}
	(*start_cmd)[j] = '\0';
	(*start_cmd)[*i++] = '\0';
	tmp = ft_strjoin(&(*start_cmd)[*i], &(*start_cmd)[j + 1]);
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	*i = j - 2;
	return ();
}

int		env_handler(char **start_cmd, int *i)
{
	int		j;
	char	*env_value;
	char	*tmp;

	j = *i + 1;
	while ((*start_cmd)[j] && ft_isin_table((*start_cmd)[j], " <>|$\'\""))
		(*start_cmd)[j++] = (*start_cmd)[j - 1];
	(*start_cmd)[j - 1] = '\0';
	env_value = getenv((*start_cmd)[i]);
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(env_value, &((*start_cmd)[j]));
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	j = 0;
	while (env_value[j])
		if (env_value[j++] == ' ')
			if (env_value[j] && env_value[j] != ' ')
				return (free(env_value), -1);
	j += *i;
	*i += ft_strlen(env_value);//peut etre -1
	free(env_value);
	return (j);
}

char	*file_name_trim(char **start_cmd, int *index, int flag)
{
	int		start_index;

	start_index = *index;
	while ((*start_cmd)[*index] != '\0' && (*start_cmd)[*index] != ' ')
	{
		if (ft_isin((*start_cmd)[*index], "<>|"))
			break;
		if ((*start_cmd)[*index] == '$')
			*index = env_handler(start_cmd, *index, flag);
		if ((*start_cmd)[*index] == '\'' || (*start_cmd)[*index] == '\"')
			*index = guille_handler(start_cmd, *index, flag);
		if (*index == -1)
			return (NULL);
		index++;
	}
	(*start_cmd)[start_index] = '\0';
	return (ft_strndup(&(*start_cmd)[start_index], *index - start_index));
	
}

int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = false;
	while (*line)
	{
		if (tokkened)
			if (ft_isin(*line, "<>|"))
				return (0);
		tokkened = ft_isin(*line, "<>|");
		if (*(line + 1) == *line && (*line == '>' || *line =='<'))
			line++;
		line++;
	}
	if (tokkened)
		return (0);
	return (1);
}

int	all_good(char *line)
{
	int	index;

	index = 0;
	if (!verif_tokken)
		return (0);
	while (line[index])
	{
		if ()
		index++;  
	}
}
