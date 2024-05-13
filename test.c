#include "minishell.h"
#define REDIRECT 1
#define F_NAME_TRIM 1

int	verif_tokken(char *line)
{
	int	tokkened;

	tokkened = 0;
	while (*line)
	{
		if (tokkened)
			if (ft_isin_table(*line, "<>|"))
				return (0);
		tokkened = ft_isin_table(*line, "<>|");
		if (*(line + 1) == *line && (*line == '>' || *line =='<'))
			line++;
		line++;
	}
	if (tokkened)
		return (0);
	return (1);
}

int		env_handler(char **start_cmd, int *i)
{
	int		j;
	char	*env_value;
	char	*tmp;

	j = *i + 1;
	//fprintf(stderr, "voici env key : %s\n", &(*start_cmd)[*i]);
	while ((*start_cmd)[j] && !ft_isin_table((*start_cmd)[j], " <>|$\'\""))
	{
		(*start_cmd)[j - 1] = (*start_cmd)[j];
		j++;//ca peut se mettre en ++j au debut de la boucle
	}
	(*start_cmd)[j - 1] = '\0';
	//fprintf(stderr, "voici env key : %s\n", &(*start_cmd)[*i]);
	env_value = getenv(&(*start_cmd)[*i]);
	(*start_cmd)[*i] = '\0';
	tmp = ft_strjoin(env_value, &((*start_cmd)[j]));
	*start_cmd = ft_strjoin_n_free(*start_cmd, tmp);
	if (env_value == NULL)
		return(*i);
	j = 0;
	while (env_value[j])
		if (env_value[j++] == ' ')
			if (env_value[j] && env_value[j] != ' ')
				return (-1);
	j += *i - 1;
	*i += ft_strlen(env_value) - 1;
	return (j);
}

int		guille_handler(char **start_cmd, int *i, int flag)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while ((*start_cmd)[j] && (*start_cmd)[j] != (*start_cmd)[*i])
	{
		if ((*start_cmd)[*i] == '\"' && (*start_cmd)[j] == '$')
			if (env_handler(start_cmd, &j) == -1 && flag == F_NAME_TRIM)
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

char	*file_name_trim(char **start_cmd, int *index)
{
	int		start_index;
	int		start_name_index;

	start_index = *index;
	*index += 1;
	while ((*start_cmd)[*index] == ' ')
		*index += 1;
	start_name_index = *index;
	while ((*start_cmd)[*index] != '\0' && (*start_cmd)[*index] != ' ')
	{
		if ((*start_cmd)[*index] == '\'' || (*start_cmd)[*index] == '\"')
			*index = guille_handler(start_cmd, index);
		else if (ft_isin_table((*start_cmd)[*index], "<>|"))
			break;
		else if ((*start_cmd)[*index] == '$')
			*index = env_handler(start_cmd, index, F_NAME_TRIM);
		else//if ((*start_cmd)[*index] && (*start_cmd)[*index] != ' ') <== je suis pas sure de pouvoir l'enlever mais je crois bien
			*index += 1;
		if (*index == -1)
			return (fprintf(stderr, "Ambiguous redirects\n"), NULL);
	}
	(*start_cmd)[start_index++] = '\0';
	fprintf(stderr, "purtant ca donne ca: %d\n", *index - start_name_index);
	return (ft_strndup(&(*start_cmd)[start_name_index], *index - start_name_index));
}

int	out_handler(char **start_cmd, int *index, int flag)
{
	int		fd;
	char	*file;
	char	*tmp;

	file = file_name_trim(start_cmd, index);
	fprintf(stderr, "this is the name : %s\n", file);
	if (file == NULL)
	{
		if (*index != ' ')
			fprintf(stderr, "there aint no file bud ;-;\n");
		return (0);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//si line too longue on peu mettre un define/cree un mod_t 00644
1	if (fd == -1)
		return(printf("wait a minute... something aint right\n"), 0);
	else if (flag == REDIRECT)
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (0);
	close(fd);
	tmp = ft_strjoin(*start_cmd, &(*start_cmd)[*index]);
	*index -= ft_strlen(file) + 2;
	(free(*start_cmd), free(file));
	*start_cmd = tmp;
	return (1);
}

t_stof	*str_to_func()
{
	t_stof	*ret;

	ret = malloc(sizeof(t_stof) * 6);
	ret[0].str = ">";
	ret[0].func = &out_handler;
	ret[1].str = NULL;
	ret[1].func = NULL;
	return (ret);
}

int	redirects(char **start_cmd, int *index, t_stof *stofs, int flag)
{
	int	i;

	i = 1 + ((*start_cmd)[*index] == (*start_cmd)[*index + 1]);
	while (stofs->str)
	{
		if (!ft_strncmp(stofs->str, &((*start_cmd)[*index]), i))
			break;
		stofs++;
	}
	fprintf(stderr, "wii uze ze fukchion : %s, %d\n", stofs->str, i);
	if (stofs->func != NULL)
		if (!stofs->func(start_cmd, index, flag))
			return (0);
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


int	main()
{
	char	*line;

	line = readline("prompt >");
	fprintf(stderr, "voici la reponse : %d\n", all_good(line));
	return (0);
}