#include "minishell.h"


//au cas ou, les apostrophes ca existe... JK'ai l'air d'avoir oublier... ;-;
//puis les >> << mais ca j'ai pas zappe X))
//penser aux codes d'erreurs

char	*surely_an_exe(char	*signe, t_list **list)
{//je passe ici un truc pour verifier si il  y a des double pipe, 
	char	*content;
	int		nbr_signe;

	content = signe;
	if (*signe != '\0')
	{
		nbr_signe = 2;
		if (signe[1] == '>' || signe[1] == '<')
			nbr_signe = 3;
		content = ft_calloc(sizeof(char), nbr_signe);
		if (!content)
			return (NULL);
		nbr_signe = 0;
		while (signe[nbr_signe] == *signe && nbr_signe < 3)//0, 1 et 2 
		{
			printf("je comprends pas : %c : %c : %d\n", content[0], content[1], nbr_signe);
			content[nbr_signe] = signe[nbr_signe];
			nbr_signe++;
			printf("je comprends pas : %c : %c : %d\n", content[0], content[1], nbr_signe);
			printf("alors que la contenus = %s\n", content);
		}
		if (nbr_signe > 2)
			return (free(content), printf("icit ? \n"),  NULL);
		ft_lstadd_back(list, ft_lstnew(content));
		ft_lstadd_front(list, ft_lstnew(ft_strdup("exec")));
	}
	if (!*list)
		(ft_lstadd_front(list, ft_lstnew(ft_strdup("exec"))), printf("tu grand mama \n"));
	*signe = '\0';//pour le split
	return (content); 
}

char	*sort_parse(char *signe, t_list **list, char *line)
{
	char	*content;
	char	**args;
	int		i;

	if (signe == line)// dans le cas ou line commence ou finis avec un signe. donc que le cote droit ou gauche n'existe pas.
		return (NULL);//free t_list with a func here
	content = surely_an_exe(signe, list);
	args = ft_split(line, ' ');//peu etre besoin de faire un split pour gerere les guillemets ? Not sure
	//add environmement variables and guillemets
	i = 0;
	ft_lstadd_front(list, ft_lstnew(args));
	if (content != signe)//rajoute le prochain type d'entree. on ne peus pas tester SIGNE != \0 a cause du split (qui nous demande de passer *signe a \0)
		ft_lstadd_front(list, ft_lstnew(ft_strdup("file")));
	if (*content)
		ft_lstlast(*list)->content = ft_strdup("exec");
	while (*line != '\0')
		line++;
	return (line + (content != signe));//a changer pour le cas de >> ou <<
}

t_list	*parse(char *line)
{
	char	*tmp;
	t_list	*ret;
	char	*tmpLine;

	tmp = line;
	tmpLine = line;
	ret = NULL;
	while (*tmp != '\0')
	{
		if (ft_isin_table(*tmp, "|><"))
			line = sort_parse(tmp, &ret, line);
		if (!line)
			return (free(tmpLine), NULL);
		if (*tmp == '\'')
			while (++*tmp != '\'')
				if (*tmp == '\0')
					return (NULL);
		else if (*tmp++ == '\"')
			while (*tmp != '\"')
				if (*tmp++ == '\0')
					return (NULL);
		tmp++;
		printf(": %d :", tmp - tmpLine);
	}
	sort_parse(tmp, &ret, line);//no need to protect it. If failed, the ret will be null
	free(tmpLine);
	printf("le contenus est sense etre : %s\n", ret->content);
	return (ret);
}