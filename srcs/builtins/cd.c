#include "../../includes/minitest.h"

static int	oldpwd_updater(t_list *env, t_list *PWD)
{
	t_list	*OLDPWD;
	char	*content;

	OLDPWD = get_env_node(env, "OLDPWD");
	if (!OLDPWD)
		return (perror("malloc"), 0);
	content = PWD->content + 3;
	content = ft_strjoin("OLDPWD", content);
	if (!content)
		return (perror("malloc"), 0);
	if (OLDPWD->content)
		free(OLDPWD->content);
	OLDPWD->content = content;
	return (1);
}

static int change_pwd(t_list *env)
{	
	t_list	*PWD;
	char	content[PATH_MAX];
	char	*tmp;

	PWD = get_env_node(env, "PWD");
	if (!oldpwd_updater(env, PWD))
		return(0);
	if (!getcwd(content, PATH_MAX))
		return (perror("getcwd"), 0);
	tmp = ft_strjoin("PWD=", content);
	if (!tmp)
		return (perror("malloc"), 0);
	free(PWD->content);
	PWD->content = tmp;
	return (1);
}

int	ft_cd(t_cmd *redirects, t_list *env, char **av)
{
	if (!av[1])
		return (ft_putestr_fd("minishell: cd: too few arguments\n", STDERR_FILENO), 0);
	if (av[2])
		return (ft_putestr_fd("minishell: cd: too many arguments\n", STDERR_FILENO), 0);
	if (chdir(av[1]) == -1)
		return (perror("cd"), 0);
	return (free_args(av), change_pwd(env));
}
