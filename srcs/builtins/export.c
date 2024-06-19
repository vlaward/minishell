#include "../../includes/minishell.h"

// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// } t_env;

// sort before print
static void	fr_export_print(t_env *lst)
{
	while (lst)
	{
		if (lst->value)
			printf("export %s=\"%s\"\n", lst->key, lst->value);
		else
			printf("export %s\n", lst->key);
		lst = lst->next;
	}
}

static void	ft_export_set(char *str, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst && ft_strcmp_key(lst->key, ft_get_key(str)))
		lst = lst->next;
	if (lst)
	{
		if (ft_strcmp_key(str, ft_get_key(str)))
		{
			free(lst->value);
			lst->value = ft_get_value(str);
		}
	}
	else
	{
		lst = tmp;
		ft_lstadd_back(&lst, ft_lstnew(str)); // does it init the value well ?
		lst = ft_lstlast(lst);
	}
}

void	ft_export(char **av, t_env *lst)
{
	int		i;

	if (!av[1])
		ft_export_print(lst);
	i = 1;
	while (av[i])
	{
		if (!ft_isvar(ft_get_key(av[i]))) // is it freed ?
		{
			printf("export: \'%s\': not a valid identifier\n", av[i]);
		}
		else
			ft_export_set(av[i], lst);
		i++;
	}
}
