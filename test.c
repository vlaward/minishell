#include "minishell.h"

char	*add_to_list(char *itterand, t_list **liste)
{//je gere pas du tout les guillemets la ;-;
	char	*start_word;
	char	*content;

	while (*itterand && *itterand == ' ')
		itterand++;
	start_word = itterand;
	printf("itterand: %s\n", start_word);
	if (*itterand && ft_isin_table(*itterand++, "\'\""))
	{
		while (*itterand && *itterand != *start_word)
			itterand++;
		start_word++;
	}
	else
		while (*itterand && !ft_isin_table(*itterand, " \'\""))
			itterand++;
	content = ft_calloc(itterand - start_word + 1, sizeof(char));
	ft_strlcpy(content, start_word, itterand - start_word + 1);
	ft_lstadd_front(liste, ft_lstnew(content));
	printf("ca passe par la : %s\n", content);
	return (itterand);
}

char	**ft_minisplit(char	*str)
{
	t_list	*will_be_ret;
	int		i;
	char	*itterand;
	char	**ret;

	itterand = str;
	will_be_ret = NULL;
	printf("ici nous avons %s\n", str);
	while (*itterand != '\0')
		itterand = add_to_list(itterand, &will_be_ret);
	ret = ft_calloc(ft_lstsize(will_be_ret) + 1, sizeof(char *));
	i = 0;
	while (ft_lstnodi(&will_be_ret, i))
		ret[i++] = ft_lstnodi(&will_be_ret, i)->content;//on pourrais faire un "do while" ici
	ft_lstclear(&will_be_ret, NULL);
	return (free(str), ret);//je faitr le free de str ici
}


int		main()
{
	char	**splited;
	char	*str;
	int		i;

	i = 0;
	str = readline("AAAHA PROOOMPT >");
	printf("icit str : %s\n", str);
	splited = ft_minisplit(str);
	while (splited[i] != NULL)
	{
		printf("\"%s\",\n", splited[i]);
		free(splited[i++]);
	}
	free(splited);
	return (0);
}

// int	main()
// {
// 	char	**cat;
// 	char	**cat2;
// 	int		pipette[2];
// 	int		status;

// 	status = 0;
// 	pipe(pipette);
// 	cat = NULL;
// 	cat = ft_split("/bin/cat test", ' ');
// 	cat2 = ft_split("/bin/cat txt", ' ');
// 	if (!fork())
// 	{
// 		dup2(pipette[1], STDOUT_FILENO);
// 		execve(cat[0], cat, NULL);
// 	}
// 	else
// 	{
// 		dup2(pipette[0], STDIN_FILENO);
// 		execve(cat2[0], cat2, NULL);
// 		// write(1, "Petite putain\n\0", 15);//on devrtais pouvoir directement ecrire dans pipe
	
// 	}
// 	return(0);
//}