#include "minishell.h"


//au cas ou, les apostrophes ca existe... JK'ai l'air d'avoir oublier... ;-;
//puis les >> << mais ca j'ai pas zappe X))

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
		content = malloc(sizeof(char) * nbr_signe);
		if (!content)
			return (NULL);
		nbr_signe = 0;
		while (signe[nbr_signe] == *signe && nbr_signe < 3)//0, 1 et 2 
			content[nbr_signe] = signe[nbr_signe++];
		if (nbr_signe > 2)
			return (free(content), printf("icit ? \n"),  NULL);
		ft_lstadd_back(list, ft_lstnew(content));
		ft_lstadd_front(list, ft_lstnew(ft_strdup("exec")));
	}
	if (!*list)
		(ft_lstadd_front(list, ft_lstnew(ft_strdup("exec"))));
	printf("content : %s\n", content);
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
	args = ft_split(line, ' ');
	//add environmement variables and guillemets
	i = 0;
	ft_lstadd_front(list, ft_lstnew(args));
	if (content != signe)//rajoute le prochain type d'entree. on ne peus pas tester SIGNE != \0 a cause du split (qui nous demande de passer *signe a \0)
		ft_lstadd_front(list, ft_lstnew(ft_strdup("file")));
	printf("content : %s\n", content);
	if (content)
		ft_lstlast(*list)->content = ft_strdup("exec");
	while (*line != '\0')
		line++;
	return (line + (content != signe));
}

t_list	*parse(char *line)
{//maybe have ret and last node together... :/ could be faster
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
		tmp++;
	}
	sort_parse(tmp, &ret, line);//no need to protect it. If failed, the ret will be null
	free(tmpLine);
	return (ret);
}
