#include "minishell.h"

// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// } t_env;

void	__unset(char **av, t_env *lst)
{
	int		i;
	t_env	*tmp;

	if (!av[1])
		return ;
	i = 1;
	tmp = lst;
	while (av[i])
	{
		if (!__isvar(av[i])) // get the fcts // get_key removed ?
		{
			printf("unset: \'%s\': not a valid identifier\n", av[i]);
		}
		else
		{
			while (lst->next && __strcmp_key(lst->next->key, av[i]))
				lst = lst->next;
			if (lst->next)
				__free_elem(lst); // free le maillon
			lst = tmp;
		}
		i++;
	}
}
