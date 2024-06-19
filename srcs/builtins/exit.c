#include "../../includes/minishell.h"

static int	__ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static void	__freexit(t_mini *mini, int excode)
{
	__free_lex(mini->lex);
	__free_tabex(mini->tmp);
	__free_lst(mini->lst);
	__free_tab(mini->cmds_path);
	free(mini->ret_tmp);
	free(mini->pipes);
	free(mini);
	exit (excode);
}

static void	__alpharg(t_mini *mini, char *str)
{
	__putstr_fd("bash: exit: ", 2);
	__putstr_fd(str, 2);
	__putstr_fd(": numeric argument required\n", 2);
	__freexit(mini, 2);
}

void	__exit(char **av, t_mini *mini)
{
	int	ac;

	ac = __ac(av);
	if (mini->tab->exec[0] && !mini->tab->next)
	{
		close(mini->fd1);
		close(mini->fd2);
		close(mini->pipes->fd_tmp);
	}
	if (ac == 0)
		__freexit(mini, g_ret);
	if (__alphastr(av[0]))
		__alpharg(mini, av[0]);
	if (ac > 1)
		__putstr_fd("bash: exit: too many arguments\n", 2);
	else
		__freexit(mini, __atoi(av[0]));
}
