#include "../../includes/minishell.h"

//put a getenv in the beginning of minishell and change all the getenvs in builtins
//also only builtin when final command ! not normal

int	ft_is_builtins(char *av)
{
	if (!ft_strcmp(av, "echo"))
		return (1);
	else if (!ft_strcmp(av, "env"))
		return (1);
	else if (!ft_strcmp(av, "unset"))
		return (1);
	else if (!ft_strcmp(av, "export"))
		return (1);
	else if (!ft_strcmp(av, "pwd"))
		return (1);
	else if (!ft_strcmp(av, "cd"))
		return (1);
	else if (!ft_strcmp(av, "exit"))
		return (1);
    else
        return (0);
}

t_env	*__tab_lst(char **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = __lstnew(env[i]);
	while (env[i])
	{
		__lstadd_back(&lst, __lstnew(env[i]));
		i++;
	}
	return (lst);
}

// add env to all of them
void	ft_builtins(char **av)
{
	// fct to change env to list
	t_env	*lst;

	if (!ft_strcmp(av[0], "echo"))
		ft_echo(av);
	else if (!ft_strcmp(av[0], "exit"))
		ft_exit(av);
	lst = __tab_lst(G_env);
	if (!ft_strcmp(av[0], "env"))
		ft_env();
	// else if (!ft_strcmp(av[0], "unset"))
	// 	ft_unset(av);
	else if (!ft_strcmp(av[0], "export"))
		ft_export(av);
	else if (!ft_strcmp(av[0], "pwd"))
		ft_pwd();
	// else if (!ft_strcmp(av[0], "cd"))
	// 	ft_cd(av);
	// fct to change env to tab
	t_env *tmp;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}