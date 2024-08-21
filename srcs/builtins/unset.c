#include "../../includes/minitest.h"

// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// } t_env;

int	ft_unset(t_cmd *redirects, t_list *env, char **av)
{
	int		i;
	t_list	*tmp;
	t_list	*incr;

	if (!av[1])
		return (0);
	i = 0;
	while (av[++i])
	{
		incr = env;
		while (incr->next != NULL && ft_strncmp(av[i], incr->next->content, ft_strlen(av[i])))
			incr = incr->next;
		if (incr->next)
		{
			tmp = incr->next;
			incr->next = tmp->next;
			ft_lstdelone(tmp, free);
		}
	}
	free_args(av);
	return (1);
}
