#include "../../includes/minitest.h"

int	dowe_write_node(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*str++ == '=')
			return (1);
	return (0);
}

int	ft_env(t_cmd *redirects, t_list *env, char **cmd)
{
	int	isout;

	isout = STDOUT_FILENO;
	if (redirects)
		isout = redirects->out;
	// if (++cmd)
	// 	return (write(STDERR_FILENO, "env : args not handled\n", 23), 0);
	while (env)
	{
		if (dowe_write_node(env->content))
		{
			if (ft_putestr_fd(env->content, isout) == -1)
				return (perror("write"), free_args(cmd), 0);
			if (ft_putechar_fd('\n', isout) == -1)
				return (perror("write"), free_args(cmd), 0);
		}
		env = env->next;
	}
	free_args(cmd);
	return (1);
}
