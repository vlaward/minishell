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
		return (NULL);
	tmp = ft_lstnodi(&towrite, i);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->content, limitter->content))
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
	if (isatty(in))
		ft_lstadd_front(&towrite, ft_lstnew(readline("> ")));
	else
		ft_lstadd_front(&towrite, ft_lstnew(get_next_line(in)));
	while (towrite != NULL)
	{
		do_we_write(&towrite, maybe_write_it(towrite, limitter), pipette);
		if (towrite != NULL)
		{
			if (isatty(in))
				ft_lstadd_front(&towrite, ft_lstnew(readline("> ")));
			else
				ft_lstadd_front(&towrite, ft_lstnew(get_next_line(in)));
		}
	}
}

char	*limit_handler(char *itterand, char *start_cmd)
{
	t_list	*limitter;
	char	*toadd;
	pid_t	pipette[2];

	while (*itterand != '<')
		if (*itterand++ == '\0')
			return (start_cmd);
	limitter = NULL;
	fprintf(stderr, "la on a itterand %s \n", itterand);
	while (*itterand && *itterand == '<')
	{
		*itterand = '\0';
		itterand += 2; 
		toadd = file_name_trim(&itterand);
		if (toadd == NULL || *toadd == '\0')
			return (fprintf(stderr, "there aint no limitter bud ;-;\n"), 	NULL);
		ft_lstadd_front(&limitter, ft_lstnew(toadd));
		while (*itterand == ' ')
			itterand++;
	}
	if (limitter == NULL)
		return (fprintf(stderr, "there aint no limitter bud ;-;\n"), NULL);
	pipe(pipette);
	limitter_redirect(STDIN_FILENO, pipette, limitter);
	free(limitter);
	return (ft_strjoin_n_free(start_cmd, ft_strdup(itterand)));
}
