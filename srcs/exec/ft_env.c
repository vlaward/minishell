#include "../../includes/minishell.h"

int		taille_env(char	**env)
{
	int	i;

	if (!env)
		return (-1);
	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	**env_from_scratch()
{
	char	**ret;
	char	*pwd;

	pwd = (char*)malloc(PATH_MAX * sizeof(char));
	getcwd(pwd, PATH_MAX * sizeof(char));
	if (!pwd)
		return (perror("malloc"), NULL);
	ret = (char**)malloc(4 * sizeof(char*));
	if (!ret)
		return (free(pwd), perror("malloc"), NULL);
	ret[0] = ft_strjoin("PWD=", pwd);
	ret[1] = ft_strdup("SHLVL=1");
	ret[2] = ft_strjoin(ret[0], "/./minishell");
	return (free(pwd), ret);
}

int	set_env(char **env)
{
	char	*tmp;

	if (!env || !*env)
		return (0);
	if (ft_strncmp(*env, "SHLVL=", 6) == 0)
	{
		tmp = ft_itoa(ft_atoi(*env + 6) + 1);
		if (!tmp)
			return (0);
		*(*env + 6) = '\0';
		*env = ft_strjoin_n_free(*env, tmp);
		if (!*env)
			return (0);
	}
	return (1);
}

char	**init_env(char	**env)
{
	char	**ret;
	int		size;

	size = taille_env(env);
	if (size <= 0)
		return (env_from_scratch());
	ret = (char**)malloc((size + 1) * sizeof(char*));//initialiser a 0 ?
	size = 0;
	if (!ret)
		return (perror("malloc"), NULL);
	while (*env)
	{
		ret[size] = ft_strdup(*env);
		if (!set_env(&ret[size++]))
		{
			while (--size >= 0)
				free(ret[size]);
			free(ret);
			return (perror("malloc"), NULL);
		}
		env++;
	}
	ret[size] = NULL;
	return (ret);
}