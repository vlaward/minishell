#include "../../includes/minishell.h"


int		env_handler(char **start_cmd, int *i, t_list *env)
{
	int		j;
	char	*env_value;
	char	*tmp;

	j = *i + 1;
	//fprintf(stderr, "voici env key : %s\n", &(*start_cmd)[*i]);
	while ((*start_cmd)[j] && !ft_isin_table((*start_cmd)[j], " <>|$\'\""))//is ispace surtout
	{
		(*start_cmd)[j - 1] = (*start_cmd)[j];
		j++;//ca peut se mettre en ++j au debut de la boucle
	}
	if (j == ++(*i))
		return (j);
	(*start_cmd)[j - 1] = '\0';
	//fprintf(stderr, "voici env key : %s\n", &(*start_cmd)[*i]);
	env_value = ft_getenv(&(*start_cmd)[*i], env);
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(env_value, &((*start_cmd)[j]));
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	if (env_value == NULL)
		return(*i);
	j = 0;
	while (env_value[j])
		if (ft_iswhitespace(env_value[j++]))
			if (env_value[j] && !ft_iswhitespace(env_value[j]))
				return (-1);
	j += *i - 1;
	*i += ft_strlen(env_value) - 1;
	return (j);
}

int		guille_handler(char **start_cmd, int *i, int flag, t_list *env)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while ((*start_cmd)[j] && (*start_cmd)[j] != (*start_cmd)[*i])
	{
		if (flag != H_DOC_TRIM && (*start_cmd)[*i] == '\"' && (*start_cmd)[j] == '$')
			if (env_handler(start_cmd, &j, env) == -1 && flag == F_NAME_TRIM)
				return (-1);
		if ((*start_cmd)[j] != '\0')
			j++;
	}
	(*start_cmd)[j] = '\0';
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(&(*start_cmd)[*i + 1], &(*start_cmd)[j + 1]);
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	*i = j - 1;	
	return (j - 1);
}

char	*trim(char **start_cmd, int *index, int flag, t_list *env)
{
	int		start_index;
	int		start_name_index;

	printf("nous voici medames et messierus avec [%s]\n\t\t et [%s]\n", *start_cmd, (*start_cmd +*index));
	start_index = *index;
	*index += 1;
	while (ft_iswhitespace((*start_cmd)[*index]))
		*index += 1;
	start_name_index = *index;
	while ((*start_cmd)[*index] != '\0' && !ft_iswhitespace((*start_cmd)[*index]))
	{
		if ((*start_cmd)[*index] == '\'' || (*start_cmd)[*index] == '\"')
			*index = guille_handler(start_cmd, index, flag, env);
		else if (ft_isin_table((*start_cmd)[*index], "<>|"))
			break;
		else if (flag != H_DOC_TRIM && (*start_cmd)[*index] == '$')
			*index = env_handler(start_cmd, index, env);
		else//if ((*start_cmd)[*index] && (*start_cmd)[*index] != ' ') <== je suis pas sure de pouvoir l'enlever mais je crois bien
			*index += 1;
		if (*index == -1)
			return (ft_putestr_fd("Ambiguous redirects\n", errno), NULL);
	}
	(*start_cmd)[start_index++] = '\0';
	//fprintf(stderr, "purtant ca donne ca: %d\n", *index - start_name_index);
	return (ft_strndup(&(*start_cmd)[start_name_index], *index - start_name_index));
}
