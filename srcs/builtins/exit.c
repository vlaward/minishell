/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:45:58 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/11 13:09:49 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_ac(char **av)
{
	char	**tmp;

	tmp = av;
	while (*tmp)
		tmp++;
	return (tmp - av);
}

int	ft_istr_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_alpharg(char **av, t_list **redirect)
{
	ft_putestr_fd(" numeric argument required\n", STDERR_FILENO);
	free_args(av);
	(ft_lstclear(redirect, free_cmd), exit(2));
}

int	ft_exit(t_list **redirect, t_list *env, char **av)
{
	int	ac;
	int	ret;

	(void)env;
	ret = 1;
	ac = ft_ac(av);
	close(TTY_SAVED_FD);
	ft_putestr_fd("exit\n", STDOUT_FILENO);
	if (redirect)
		ft_lstclear(redirect, free_cmd);
	if (ac == 1)
		(ft_lstclear(&env, free), free_args(av), exit(0));
	if (!ft_istr_num(av[1]))
		(ft_lstclear(&env, free), ft_alpharg(av, redirect));
	if (ac > 2)
		(ft_putestr_fd(" too many arguments\n"
				, STDERR_FILENO), free_args(av), exit(1));
	ret = ft_atoi(av[1]);
	(ft_lstclear(&env, free), free_args(av), exit(ret));
}
