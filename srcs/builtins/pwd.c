#include "../../includes/minitest.h"

#define PWDK_L 4

//une fois cd fait a changer ?
int	ft_pwd(t_cmd *redirects, t_list *env, char **cmd)
{
	char	*path;
	int		isout;

	isout = STDOUT_FILENO;
	if (redirects)
		isout = redirects->out;
	if (ft_putestr_fd(ft_getenv("PWD", env), isout) == -1)
		return (free_args(cmd) ,perror("write"), 0);
	if (ft_putechar_fd('\n', isout) == -1)
		return (free_args(cmd) ,perror("write"), 0);
	free_args(cmd);
	return (1);
}


// int	ft_pwd(t_cmd *redirects, t_list *env, char **cmd)
// {
// 	char	s[PATH_MAX]; //create buffer to store return value of getcwd

// 	printf("%s\n", getcwd(s, PATH_MAX));
// }
