#include "minishell.h"


//au cas ou, les apostrophes ca existe... JK'ai l'air d'avoir oublier... ;-;
//puis les >> << mais ca j'ai pas zappe X))

char	*sort_parse(char *signe, t_list **list, char *line)
{
	char	*content;
	char	**args;
	int		i;

	content = signe;
	if (*signe != '\0')
	{
		content = malloc(sizeof(char) * 2);
		content[1] = '\0';
		content[0] = *signe;
		ft_lstadd_back(list, ft_lstnew(content));
		ft_lstadd_front(list, ft_lstnew(ft_strdup("exec")));
		//ajouter le "exe"
	}
	if (!*list)
		(ft_lstadd_front(list, ft_lstnew(ft_strdup("exec"))));
	*signe = '\0';
	args = ft_split(line, ' ');
	//add environmement variables and guillemets
	i = 0;
	ft_lstadd_front(list, ft_lstnew(args));
	if (content != signe)
		ft_lstadd_front(list, ft_lstnew(ft_strdup("file")));
	if (content != signe && content[0] == '|')
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
		tmp++;
	}
	sort_parse(tmp, &ret, line);

	free(tmpLine);
	return (ret);
}
