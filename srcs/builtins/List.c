#include "minishell.h"

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