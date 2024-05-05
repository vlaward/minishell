#include "minishell.h"

void	__unset(char **av, t_env *lst)
{
	int		i;
	t_env	*tmp;

	if (!av[0])
		printf("unset: not enough arguments\n");
	i = 0;
	tmp = lst;
	while (av[i])
	{
		if (!__isvar(__get_key(av[i])))
		{
			printf("unset: \'%s\': not a valid identifier\n", av[i]);
			g_ret = 1;
		}
		else
		{
			while (lst->next && __strcmp_key(lst->next->key, __get_key(av[i])))
				lst = lst->next;
			if (lst->next)
				__free_elem(lst);
			lst = tmp;
			g_ret = 0;
		}
		i++;
	}
}
