#include "../../includes/minishell.h"

/*
// if env en list
void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
*/

// if env en char **
void	ft_env(void)
{
	int	i;

	i = 0;
	while (G_env[i])
	{
		printf("%s\n", G_env[i]);
		i++;
	}
}
