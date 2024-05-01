#include <unistd.h>

// remove in prod and link to libft
int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (*str++ != '\0')
		n++;
	return (n);
}

static int	ft_option(char *av)
{
	int	i;

	i = 1;
	if (!av[0])
		return (0);	
	if (av[0] != '-')
		return (0);
	while (av[i] == 'n')
		i++;
	if (av[i] != 'n' && av[i] != '\0')
		return (0);
	if (av[1] == '\0')
		return (0);
	return (1);
}

void	ft_echo(char **av)
{
	int	i;

	i = 1;
	while (av[i] && ft_option(av[i]))
		i++;
	while (av[i])
	{
		write(1, av[i], ft_strlen(av[i]));
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (!ft_option(av[1]))
		write(1, "\n", 1);
}

int	main(int ac, char **av, char **env)
{
	ft_echo(av);
	return (0);
}
