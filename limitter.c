#include "minishell.h"

int	do_we_write(t_list **towrite, t_list *limitter, pid_t pipette[0])
{
	t_list	 *freele;

	if (limitter == NULL)
		return (0);
	dup2(pipette[0], STDIN_FILENO);
	while (*towrite != limitter)
	{
		freele = *towrite;
		ft_putestr_fd((*towrite)->content, pipette[1]);
		*towrite = (*towrite)->next;
		ft_lstdelone(freele, &free);
		ft_putechar_fd('\n', pipette[1]);
	}
	close(pipette[0]);
	close(pipette[1]);
	ft_lstclear(&limitter, &free);
	*towrite = NULL;//juste pour etre safe
	return (1);
}

t_list	*maybe_write_it(t_list *towrite, t_list *limitter)
{
	t_list	*tmp;
	int		i;

	i = ft_lstsize(towrite) - ft_lstsize(limitter);
	if (i < 0)
		return (fprintf(stderr, "ceti lo ?\n"), NULL);
	tmp = ft_lstnodi(&towrite, i);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->content, limitter->content) != 0)
			return (NULL);
		tmp = tmp->next;
		limitter = limitter->next;
	}
	return(ft_lstnodi(&towrite, i));
}

void	limitter_redirect(pid_t in, pid_t pipette[2],  t_list *limitter)
{
	t_list	*towrite;

	towrite = NULL;
	if (!isatty(in))
		return ;
	ft_lstadd_front(&towrite, ft_lstnew(readline("> ")));
	while (towrite != NULL)
	{
		do_we_write(&towrite, maybe_write_it(towrite, limitter), pipette);
		if (towrite != NULL)
				ft_lstadd_front(&towrite, ft_lstnew(readline("> ")));
	}
}

int	add_to_limitter(char **start_cmd, int *index, t_list **limitter)
{
	char	*toadd;
	int		size_soustraire;

	(*start_cmd)[*index] = '\0';
	*index += 1; 
	toadd = trim(start_cmd, index, H_DOC_TRIM);
	size_soustraire = ft_strlen(toadd);
	fprintf(stderr, "voici le limitter : \'%s\'\n", toadd);
	if (toadd == NULL || *toadd == '\0')
		return (fprintf(stderr, "syntax error my cul\n"), 0);
	ft_lstadd_front(limitter, ft_lstnew(toadd));
	toadd = *start_cmd;
	*start_cmd = ft_strjoin(*start_cmd, &((*start_cmd)[*index]));
	free(toadd);
	*index -= size_soustraire;
	return (1);
}

int	here_doc(char **start_cmd)
{
	t_list	*limitter;
	pid_t	pipette[2];
	int		index;

	index = 0;
	limitter = NULL;
	while ((*start_cmd)[index])
	{
		if (ft_strncmp(&((*start_cmd)[index]), "<<", 2) == 0)
			if (!add_to_limitter(start_cmd, &index, &limitter))
				return (0);
		if ((*start_cmd)[index])
			index += 1;
	}
	if (limitter == NULL)
		return (fprintf(stderr, "c'est pas une erreur y'as jsute pass de here doc\n"), 0);
	pipe(pipette);
	limitter_redirect(STDIN_FILENO, pipette, limitter);
	free(limitter);
	return (1);
}
