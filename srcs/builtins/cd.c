#include "../../includes/minishell.h"

static int	__ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static char	*__strdup(char *str)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (__strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

static void	__change_pwd(t_env *lst)
{
	t_env	*tmp;
	char	*new;
	char	s[100];

	tmp = lst;
	while (lst)
	{
		if (!__strcmp("PWD", lst->key))
		{
			new = lst->value;
			lst->value = __strdup(getcwd(s, 100));
		}
		lst = lst->next;
	}
	lst = tmp;
	while (lst)
	{
		if (!__strcmp("OLDPWD", lst->key))
		{
			free(lst->value);
			lst->value = new;
		}
		lst = lst->next;
	}
}

void	__cd(char **av, t_env *lst)
{
	if (__ac(av) == 0)
	{
		__errorput("minishell: cd: too few arguments\n");
		return ;
	}	
	if (__ac(av) > 1)
	{
		__errorput("minishell: cd: too many arguments\n");
		return ;
	}
	if (chdir(av[0]) == -1)
	{
		__ret_perror("cd");
		return ;
	}
	__change_pwd(lst);
	g_ret = 0;
}
