// sort before print
static void	__export_print(t_env *lst)
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

static void	__export_set(char *str, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst && __strcmp_key(lst->key, __get_key(str)))
		lst = lst->next;
	if (lst)
	{
		if (__strcmp_key(str, __get_key(str)))
		{
			free(lst->value);
			lst->value = __get_value(str);
		}
	}
	else
	{
		lst = tmp;
		__lstadd_back(&lst, __lstnew(str));
		lst = __lstlast(lst);
	}
	g_ret = 0;
}

void	__export(char **av, t_env *lst)
{
	int		i;

	if (!av[0])
		__export_print(lst);
	i = 0;
	while (av[i])
	{
		if (!__isvar(__get_key(av[i])))
		{
			printf("export: \'%s\': not a valid identifier\n", av[i]);
			g_ret = 1;
		}
		else
			__export_set(av[i], lst);
		i++;
	}
}
