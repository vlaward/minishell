/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:45:58 by ncrombez          #+#    #+#             */
/*   Updated: 2024/10/06 21:33:24 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitest.h"

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
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_alpharg(char *str, t_list **redirect)
{
	ft_putestr_fd("bash: exit: ", STDOUT_FILENO);
	ft_putestr_fd(str, STDOUT_FILENO);
	ft_putestr_fd(": numeric argument required\n", STDOUT_FILENO);
	(ft_lstclear(redirect, free_cmd), exit(2));
}

//exit not exiting, add close and free ?
int	ft_exit(t_list **redirect, t_list *env, char **av)
{
	int	ac;

	(void)env;
	ac = ft_ac(av);
	ft_putestr_fd("exit", STDOUT_FILENO);
	if (!redirect)
		(ft_lstclear(&env, free), free_args(av));
	if (ac == 1)
		(ft_lstclear(redirect, free_cmd), exit(127));
	if (!ft_istr_num(av[1]))
		ft_alpharg(av[1], redirect);
	if (ac > 2)
		ft_putestr_fd("bash: exit: too many arguments\n", STDOUT_FILENO);
	else
		(ft_lstclear(redirect, free_cmd), exit(ft_atoi(av[1])));
	(ft_lstclear(redirect, free_cmd), exit(1));
}
