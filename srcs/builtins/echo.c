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
	bkslsh_n = 0;
	while (++cmd && !ft_strcmp(*cmd, "-n"))
		bkslsh_n = 1;
	while (*cmd)
		ft_putestr_fd(*(cmd++), isout);
	ft_putechar_fd('\n' * bkslsh_n, isout);
	cmd = tmp;
	while (*cmd)
		free(*(cmd++));
	free(tmp);
	return (1);
}