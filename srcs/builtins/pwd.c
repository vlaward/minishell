#include "minishell.h"

void	ft_pwd(void)
{
	char	s[100]; //create buffer to store return value of getcwd

	printf("%s\n", getcwd(s, 100));
}
