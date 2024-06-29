#include "../../includes/minishell.h"

// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// } t_env;

// sort before print
static void	ft_export_print(t_env *lst)
{
	while (lst)
	{
		if (lst->value)
			printf("export %s=\"%s\"\n", lst->key, lst->value);
		else
			printf("export %s\n", lst->key);
		lst = lst->next;
	}
}

char	*ft_get_value(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(str + i)));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

char	*ft_get_key(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

int	ft_strcmp_key(char *s1, char *s2)
{
	int	i;
	int	ret;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	ret = (unsigned char)s1[i] - (unsigned char)s2[i];
	free(s2);
	return (ret);
}

t_env	*__lstnew(void *content);

t_env	*__lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	__lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = __lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

static void	ft_export_set(char *str, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst && ft_strcmp_key(lst->key, ft_get_key(str)))
		lst = lst->next;
	if (lst)
	{
		if (ft_strcmp_key(str, ft_get_key(str)))
		{
			free(lst->value);
			lst->value = ft_get_value(str);
		}
	}
	else
	{
		lst = tmp;
		__lstadd_back(&lst, __lstnew(str)); // does it init the value well ?
		lst = __lstlast(lst);
	}
	for (t_env *tm = lst; tm; tm = tm->next)
	{
		printf("key: %s\n", tm->key);
		printf("value: %s\n", tm->value);
	}
}

char	*__join(char *s1, char *s2)
{
	int		i;
	char	*array;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	array = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!array)
		return (NULL);
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		array[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	array[i] = '\0';
	return (array);
}

static void	__strcpy(char *dst, char *src1, char *src2)
{
	while (*src1)
		*dst++ = *src1++;
	*dst++ = '=';
	while (*src2)
		*dst++ = *src2++;
}

char	*__strjoin(char *s1, char *s2)
{
	char	*res;
	int		len;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	__strcpy(res, s1, s2);
	res[len + 1] = '\0';
	return (res);
}

char	**__lst_tab(t_env *env)
{
	char	**tab;
	t_env	*tmp;
	int		i;

	i = 0;
	
	tmp = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	env = tmp;
	while (env)
	{
		tab[i] = __strjoin(env->key, env->value);
		env = env->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

t_env	*__lstnew(void *content)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = ft_get_key(content);
	elem->value = ft_get_value(content);
	elem->next = NULL;
	return (elem);
}

t_env	*__tab_lst(char **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = __lstnew(env[i]);
	while (env[i])
	{
		__lstadd_back(&lst, __lstnew(env[i]));
		i++;
	}
	return (lst);
}

t_env	*__init(char **tab)
{
	t_env	*lst;

	lst = __tab_lst(tab);
	return (lst);
}

int	__isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	__isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isvar(char *str)
{
	int		i;

	if (str[0])
	{
		if (!__isalpha(str[0]))
		{
			free(str);
			return (0);
		}
	}
	i = 1;
	while (str[i])
	{
		if (!__isalnum(str[i]))
		{
			free(str);
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

void	ft_export(char **av)
{
	int		i;
	t_env	*env;

	env = __init(G_env);
	if (!av[1])
		ft_export_print(env);
	i = 1;
	while (av[i])
	{
		if (!ft_isvar(ft_get_key(av[i]))) // is it freed ?
		{
			printf("export: \'%s\': not a valid identifier\n", av[i]);
		}
		else
			ft_export_set(av[i], env);
		i++;
	}
	i = 0;
	while (G_env[i])
	{
		free(G_env[i]);
		i++;
	}
	free(G_env);
	G_env = __lst_tab(env);
}

