#include "../../includes/minitest.h"

//put a getenv in the beginning of minishell and change all the vs in builtins
//also only builtin when final command ! not normal

int	ft_cmp_cmd_to_builtin(char *cmd, char *builtin)
{
	while (*builtin)
	{
		if (*builtin != *cmd)
			return (0);
		builtin++;
		cmd++;
	}
	if (*cmd == ' ' || *cmd == '\0')
		return (1);
	return (0);
}

f_builtin	ft_builtins(t_cmd *cmd)
{
	char	*str;

	str = cmd->cmd;
	if (!ft_cmp_cmd_to_builtin(str	, "echo"))
		return (ft_echo);
	if (!ft_cmp_cmd_to_builtin(str, "env"))
		return (NULL);
	if (!ft_cmp_cmd_to_builtin(str, "unset"))
		return (NULL);
	if (!ft_cmp_cmd_to_builtin(str, "export"))
		return (NULL);
	if (!ft_cmp_cmd_to_builtin(str, "pwd"))
		return (NULL);
	if (!ft_cmp_cmd_to_builtin(str, "cd"))
		return (NULL);
	if (!ft_cmp_cmd_to_builtin(str, "exit"))
		return (NULL);
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