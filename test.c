#include "minishell.h"

// char	*add_to_list(char *itterand, t_list **liste)
// {//je gere pas du tout les guillemets la ;-; || Maintenant c'est bon ;p 
// 	char	*start_word;
// 	char	chose_your_guillemet;
// 	char	*content;

// 	while (*itterand && *itterand == ' ')
// 		itterand++;
// 	start_word = itterand;
// 	while (*itterand && *itterand != ' ')
// 	{
// 		if (ft_isin_table(*itterand, "\'\""))
// 		{
// 			chose_your_guillemet = *itterand;
// 			ft_memcpy(itterand, itterand + 1, ft_strlen(itterand));
// 			while ( *itterand && *itterand != chose_your_guillemet)
// 				itterand++;
// 			ft_memcpy(itterand, itterand + 1, ft_strlen(itterand));
// 		}
// 		else
// 			itterand++;
// 	}
// 	content = ft_calloc(itterand - start_word + 1, sizeof(char));
// 	ft_strlcpy(content, start_word, itterand - start_word + 1);
// 	ft_lstadd_front(liste, ft_lstnew(content));
// 	return (itterand);
// }

// char	**ft_minisplit(char	*str)
// {
// 	t_list	*will_be_ret;
// 	int		i;
// 	char	*itterand;
// 	char	**ret;

// 	itterand = str;
// 	will_be_ret = NULL;
// 	while (*itterand != '\0')
// 		itterand = add_to_list(itterand, &will_be_ret);
// 	ret = ft_calloc(ft_lstsize(will_be_ret) + 1, sizeof(char *));
// 	i = 0;
// 	while (ft_lstnodi(&will_be_ret, i))
// 		ret[i++] = ft_lstnodi(&will_be_ret, i)->content;//on pourrais faire un "do while" ici
// 	ft_lstclear(&will_be_ret, NULL);
// 	return (free(str), ret);//je faitr le free de str ici
// }

// char	*tatu_ferme_tes_guillemets(char *str);//il faut la declarer avant sinon ca fait chier

// char	*bah_ferme_les(char *str)
// {
// 	char	*one;
// 	char	*another_one;
// 	char	*and_another_one;

// 	one = readline("> ");
// 	another_one = ft_strjoin(str, "\n");
// 	and_another_one = ft_strjoin(another_one, one);
// 	(free(one), free(another_one), free(str));
// 	return (tatu_ferme_tes_guillemets(and_another_one));//pas des plus opti mais en vrais 	
// }

// char	*tatu_ferme_tes_guillemets(char *str)//faut changer les noms pour la norme mdr
// {
// 	char	*voyage;
// 	char	this_one;
	
// 	voyage = str;
// 	while (*voyage)
// 	{
// 		if (*voyage == '\"' || *voyage == '\'')
// 		{
// 			this_one = *voyage++;
// 			while (*voyage && *voyage != this_one)
// 				voyage++;
// 			if (*voyage == '\0')
// 				return (bah_ferme_les(str));
// 		}
// 		voyage++;
// 	}
// 	return (str);
// }



// int		main()
// {
// 	char	**splited;
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	str = tatu_ferme_tes_guillemets(readline("AAAHA PROOOMPT >"));
// 	splited = ft_minisplit(str);
// 	while (splited[i] != NULL)
// 	{
// 		printf("%s : ", splited[i]);
// 		free(splited[i++]);
// 	}
// 	free(splited);
// 	return (0);
// }

int	main()
{
	char	**cat;
	char	**cat2;
	int		pipette[2];
	int		status;

	status = 0;
	pipe(pipette);
	cat = NULL;
	cat = ft_split("/bin/cat test", ' ');
	cat2 = ft_split("/bin/cat txt", ' ');
	if (!fork())
	{
		dup2(pipette[1], STDOUT_FILENO);
		execve(cat[0], cat, NULL);
	}
	else
	{
		dup2(pipette[0], STDIN_FILENO);
		execve(cat2[0], cat2, NULL);
		// write(1, "Petite putain\n\0", 15);//on devrtais pouvoir directement ecrire dans pipe
	
	}
	return(0);
}