#include "minishell.h"

#ifndef PATH_MAX
# define PATH_MAX 4096
# endif

int	main()
{
	char	*line;
	char	*prompt;
	t_list	*list;

	prompt = malloc(PATH_MAX * sizeof(char));
	getcwd(prompt, PATH_MAX * sizeof(char));
	prompt = ft_strjoin(prompt, "> ");
	while (1)// add signal global test
	{
		line = readline(prompt);
		add_history(line);
		list = parse(line);
		executeur(list);
		ft_lstclear(&list, &free);
		//free la list pour sur ici
		rl_on_new_line();
	}	
	return (0);
}
