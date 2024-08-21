#include "../../includes/minitest.h"

//put a getenv in the beginning of minishell and change all the vs in builtins
//also only builtin when final command ! not normal

void	free_args(char **args)
{
	char	**tmp;

	tmp = args;
	while (*tmp)
		free(*(tmp++));
	free(args);
}

int	builtin_cmp(const char *str, const char *builtin)
{
	char tmp;

	if (ft_strncmp(str, builtin, ft_strlen(builtin)))
		return (0);
	tmp = *(builtin + ft_strlen(builtin));
	if (ft_iswhitespace(tmp) || !tmp)
		return (1);
	return (0);
}

f_builtin	ft_builtins(char *str)
{
	if (builtin_cmp(str, "echo"))
		return (ft_echo);
	if (builtin_cmp(str, "env"))
		return (ft_env);
	if (builtin_cmp(str, "unset"))
		return (ft_unset);
	if (builtin_cmp(str, "export"))
		return (ft_export);
	if (builtin_cmp(str, "pwd"))
		return (ft_pwd);
	if (builtin_cmp(str, "cd"))
		return (ft_cd);
	if (builtin_cmp(str, "exit"))
		return (ft_exit);
	return (NULL);
}

// t_env	*__tab_lst(char **env)
// {
// 	int		i;
// 	t_env	*lst;

// 	i = 0;
// 	lst = __lstnew(env[i]);
// 	while (env[i])
// 	{
// 		__lstadd_back(&lst, __lstnew(env[i]));
// 		i++;
// 	}
// 	return (lst);
// }

// // // add env to all of them
// void	ft_builtins(char **av)
// {
// 	// fct to change env to list
// 	t_env	*lst;

// 	if (!ft_strcmp(av[0], "echo"))
// 		ft_echo(av);
// 	else if (!ft_strcmp(av[0], "exit"))
// 		ft_exit(av);
// 	lst = __tab_lst(G_env);
// 	if (!ft_strcmp(av[0], "env"))
// 		ft_env();
// 	// else if (!ft_strcmp(av[0], "unset"))
// 	// 	ft_unset(av);
// 	else if (!ft_strcmp(av[0], "export"))
// 		ft_export(av);
// 	else if (!ft_strcmp(av[0], "pwd"))
// 		ft_pwd();
// 	// else if (!ft_strcmp(av[0], "cd"))
// 	// 	ft_cd(av);
// 	// fct to change env to tab
// 	t_env *tmp;
// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 	}
// }