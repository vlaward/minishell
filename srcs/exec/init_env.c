#define MIN_ENV_SIZE 3
#include "../../includes/minishell.h"

char	*ft_getenv(const char *name, t_list *env)
{
	int		size;

	if (!name)
		return("$");
	if (!env)
		return (NULL);
	if (*name == '?')
		return (env->content);
	size = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(name, env->content, size) == 0)
		{
			if (*((char *)env->content + size) == '=')
		 		return (env->content + size + 1);
		}
		env = env->next;
	}
	return (NULL);

}

t_list	*env_from_scratch(t_list *ret)
{
	char	*cwd;
	char	*tmp;

	cwd = (char *)ft_calloc(PATH_MAX, sizeof(char ));
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strjoin("PWD=", cwd)))
		|| !ft_lstlast(ret)->content)
		 return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strdup("SHLVL=1")))
		|| !ft_lstlast(ret)->content)
		return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	tmp = ft_strjoin("_=", cwd);
	if (!tmp)
		return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strjoin(tmp, "/./minishell")))
		|| !ft_lstlast(ret)->content)
		return (ft_lstclear(&ret, free), free(tmp), perror("malloc"), NULL);
	return (ret);
	}

char	*shlvl_increment(char	*env)
{
	char	*nbr;
	char	*ret;

	nbr = ft_itoa(ft_atoi(env + 6) + 1);
	if (!nbr)
		return (NULL);
	ret = ft_strjoin("SHLVL=", nbr);
	return (free(nbr), ret);
}


t_list	*init_env(char **env)
{
	t_list	*ret;
	char	*content;

	content = ft_strdup("0");
	if (!content)
		return (perror("malloc"), NULL);
	ret = ft_lstnew(content);
	if (!ret)
		return (perror("malloc"), free(content), NULL);
	if (!env || !*env)
		return (env_from_scratch(ret));
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 5) == 0)
			ft_lstadd_front(&ret, ft_lstnew(shlvl_increment(*(env++))));
		else
			ft_lstadd_front(&ret, ft_lstnew(ft_strdup(*(env++))));
		if (!ft_lstlast(ret)->content)
			return (ft_lstclear(&ret, free), perror("malloc"), NULL);//<===============================FREE THE FUCKING TABLE DON'T YOU FORGET U SUCKER (of course use ret 'caus you ain't dumb)
	}
	return (ret);
}
