#include "../../includes/minitest.h"

int	ft_option(char **str)
{
	int	i;

	i = 0;
	while (!ft_iswhitespace(**str))
		(*str)++;
	while (ft_iswhitespace(**str))
		(*str)++;
	while (**str && !ft_strncmp(*str, "-n", 2))
	{
		i = 1;
		if (ft_iswhitespace(*((*str) + 2)))
			*str += 2;
		while (ft_iswhitespace(**str))
			(**str)++;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd, t_list *env)
{
	char	*str;
	int		bkslsh_n;

	str = cmd->cmd;
	bkslsh_n = ft_option(&str);
	ft_putestr_fd(str, cmd->out);
		ft_putechar_fd('\n' * bkslsh_n, cmd->out);
	return (1);
}
