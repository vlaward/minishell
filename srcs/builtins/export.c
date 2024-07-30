#include "../../includes/minitest.h"

t_list	*get_env_node(t_list *env, char *str)
{
	int		size;

	if (!env)
		return (NULL);
	size = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(name, env->content, size) == 0)
			if (*((char *)env->content + size) == '=')
		 		return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_node_key()
{
 
}

int	ft_isvar(char *str)
{
	int		i;

	if (!ft_isalpha(str[0]))
		return (free(str), 0);
	i = 0;
	while (str[i])
		if (!ft_isalnum(str[i++]))
			return (free(str), 0);
	free(str);
	return (1);
}

void	ft_export(char **av)
{
	int		i;
	if (!av[1])
		ft_export_print(env);
	i = 1;
	while (av[i])
	{
		if (!ft_isvar(ft_get_key(av[i]))) // is it freed ?
			printf("export: \'%s\': not a valid identifier\n", av[i]);
		else
			ft_export_set(av[i], env);
		i++;
	}
	free_args(av);
}

