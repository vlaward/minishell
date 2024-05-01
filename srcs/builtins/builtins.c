#include "minishell.h"

int	ft_is_builtins(char *av)
{
	if (!ft_strcmp(av, "echo"))
		return (1);
	else if (!ft_strcmp(av, "env"))
		return (1);
	// else if (!ft_strcmp(av, "unset"))
	// 	return (1);
	// else if (!ft_strcmp(av, "export"))
	// 	return (1);
	// else if (!ft_strcmp(av, "pwd"))
	// 	return (1);
	// else if (!ft_strcmp(av, "cd"))
	// 	return (1);
	// else if (!ft_strcmp(av, "exit"))
	// 	return (1);
    else
        return (0);
}

// add env to all of them
void	ft_builtins(char **av)
{
	if (!ft_strcmp(av[0], "echo"))
		ft_echo(av);
	else if (!ft_strcmp(av[0], "env"))
		ft_env(av); // need to add env instead of av
	// else if (!ft_strcmp(av[0], "unset"))
	// 	ft_unset(av);
	// else if (!ft_strcmp(av[0], "export"))
	// 	ft_export(av);
	// else if (!ft_strcmp(av[0], "pwd"))
	// 	ft_pwd(av);
	// else if (!ft_strcmp(av[0], "cd"))
	// 	ft_cd(av);
	// else if (!ft_strcmp(av[0], "exit"))
	// 	ft_exit(av);
}