#include "minishell.h"

int G_sig_catcher;

void	sa_c_handler()
{
	G_sig_catcher = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sa_c_waiting_handler()
{
	printf("\n");
	G_sig_catcher = 1;
}

void	sa_exit_handler(int sig)
{
	fprintf(stderr, "putain de merde\n");
	exit(sig);
}


int	gere_sig(int flag)
{
	struct sigaction	sa_c;
	struct sigaction	sa_d;

	sa_c.sa_handler	 = sa_c_waiting_handler;
	if (flag == EXECUTING_CMD)
		sa_d.sa_handler	 = sa_exit_handler;
	if (flag == READING_LINE)
		sa_c.sa_handler	 = sa_c_handler;
	sa_d.sa_handler = sa_exit_handler;
	sigemptyset(&sa_c.sa_mask);
	sigemptyset(&sa_d.sa_mask);
	sa_c.sa_flags = SA_RESTART;
	sa_d.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_c, NULL) == -1)
		return (perror("minishel :"), 0);
	if (sigaction(SIGQUIT, &sa_d, NULL) == -1)
		return (perror("minishel :"), 0);
	return (1);
}