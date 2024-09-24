#include "../../includes/minitest.h"

int	ft_echo(t_cmd *redirect, t_list *env, char **cmd)
{
	int	bkslsh_n;
	char	**tmp;
	int		isout;

	isout = STDOUT_FILENO;
	if (redirect)
		isout = redirect->out;
	tmp = cmd;
	bkslsh_n = 1;
	while (++cmd && !ft_strcmp(*cmd, "-n"))
		bkslsh_n = 0;
	while (*cmd)
	{
		if (ft_putestr_fd(*(cmd++), isout) == -1)
			return (perror("write"), free_args(cmd), 0);
		if (cmd != tmp)
			if (ft_putechar_fd(' ', isout) == -1)
				return (perror("write"), free_args(cmd), 0);
		
	}
	if (ft_putechar_fd('\n' * bkslsh_n, isout) == -1)
		return (perror("write"), free_args(cmd), 0);
	//cmd = tmp;
	//free_args(cmd);
	free_args(tmp);
	//free_cmd(redirect);
	return (1);
}



