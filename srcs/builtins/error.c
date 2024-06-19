#include "../../includes/minishell.h"

void	ft_ret_perror(char *str)
{
	if (errno != 0)
		perror(str);
	g_ret = 1;
}
