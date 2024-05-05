#include "minishell.h"

void	__pwd(t_env *env)
{
	char	s[100];

	(void)env;
	printf("%s\n", getcwd(s, 100));
	g_ret = 0;
}
