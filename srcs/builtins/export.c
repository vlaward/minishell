/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:46:01 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/12 15:28:18 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_env_node(t_list *env, char *str)
{
	int		size;
	t_list	*tmp;

	tmp = env;
	if (!env)
		return (NULL);
	size = 0;
	while (str[size] && str[size] != '=' && str[size] != '+')
		size++;
	while (env)
	{
		if (ft_strncmp(str, env->content, size) == 0)
			if (*((char *)env->content + size) == '='
				|| *((char *)env->content + size) == '=')
				return (env);
		env = env->next;
	}
	if (!ft_lstadd_front(&tmp, ft_lstnew(NULL)))
		return (NULL);
	return (ft_lstlast(tmp));
}

int	append_env(t_list *node, char *str)
{
	char	*tmp;

	if (!node)
		return (0);
	if (node->content == NULL)
	{
		tmp = str;
		while (*str && *str != '+')
			str++;
		*str++ = '\0';
		node->content = ft_strjoin(tmp, str);
		return (node->content != NULL);
	}
	while (*str && *str != '=')
		str++;
	tmp = ft_strjoin(node->content, ++str);
	if (!tmp)
		return (0);
	free(node->content);
	node->content = tmp;
	return (1);
}

char	ft_isvar(char *str)
{
	if (!ft_isalpha(*str++))
		return (-1);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str))
		{
			if (*str++ == '+' && *str == '=')
				return ('+');
			return (-1);
		}
		str++;
	}
	if (*str)
		return ('=');
	return (0);
}

int	ft_export(t_list **redirect, t_list *env, char **av)
{
	int		i;
	char	type;

	if (!av[1])
		return (1);
	i = 1;
	while (av[i])
	{
		type = ft_isvar(av[i]);
		if (type <= 0)
			return (ft_lstclear(redirect, free_cmd)
				, export_error(av[i], type), free_args(av), type == -1);
		if (type == '=')
			get_env_node(env, av[i])->content = ft_strdup(av[i]);
		else
			if (!append_env(get_env_node(env, av[i]), av[i]))
				return (ft_lstclear(redirect, free_cmd), free_args(av), -1);
		if (!get_env_node(env, av[i]) || !get_env_node(env, av[i])->content)
			return (ft_lstclear(redirect, free_cmd), free_args(av), -1);
		i++;
	}
	(free_args(av), (void)redirects);
	return (ft_lstclear(redirect, free_cmd), 0);
}
