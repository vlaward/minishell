#include <unistd.h>

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

int	main(int ac, char **av, char **env)
{
	//ft_echo(av);
	printf("est ce qu'il y a une option : %d\n", ft_option(av[1]));
	return (0);
}

void	ft_echo(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i])
	{

	}
}
