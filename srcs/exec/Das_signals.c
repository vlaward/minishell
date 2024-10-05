/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Das_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:21:58 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/05 06:46:14 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sa_c_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sa_c_waiting_handler(int sig)
{
	(void)sig;
}

void	sa_c_guillemets_handler(int sig)
{
	(void)sig;
}

void	sa_exit_handler(int sig)
{
	write(STDOUT_FILENO, "\0", 1);
	exit(sig);
}

int	gere_sig(int flag)
{
	struct sigaction	sa_c;

	sa_c.sa_handler = sa_c_waiting_handler;
	if (flag == READING_LINE)
		sa_c.sa_handler = sa_c_handler;
	if (flag == EXECUTING_CMD)
		sa_c.sa_handler = sa_exit_handler;
	if (flag == GUILLEMETS)
		sa_c.sa_handler = sa_c_guillemets_handler;
	sigemptyset(&sa_c.sa_mask);
	sa_c.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_c, NULL) == -1)
		return (perror("minishel :"), 0);
	return (1);
}
