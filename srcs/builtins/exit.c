#include "../../includes/minishell.h"

static int	ft_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static int	ft_alphastr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_alpharg(char *str)
{
	ft_putestr_fd("bash: exit: ", 2);
	ft_putestr_fd(str, 2);
	ft_putestr_fd(": numeric argument required\n", 2);
	exit(2);
}

//exit not exiting, add close and free ?
void	ft_exit(char **av)
{
	int	ac;

	ac = ft_ac(av);
	//close pipes maybe ?
	if (ac == 1)
		exit(127);//changer avec valeur actuelle de retour
	if (ft_alphastr(av[1]))
		ft_alpharg(av[1]);
	if (ac > 2)
		ft_putestr_fd("bash: exit: too many arguments\n", 2);
	else
		exit(ft_atoi(av[0]));
}
