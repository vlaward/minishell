#include "../../includes/minishell.h"

/*
// a mettre dans .h
////////////////////
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;
////////////////////
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
void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
