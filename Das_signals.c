#include "minishell.h"

int	G_sig_catcher;

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
	printf("\n");
}

void	sa_exit_handler(int sig)
{
	fprintf(stderr, "putain de merde\n");
	write(STDIN_FILENO, "\0", 1);
	exit(sig);
}

int	gere_sig(int flag)
{
	struct sigaction	sa_c;

	sa_c.sa_handler = sa_c_waiting_handler;
	if (flag == READING_LINE)
		sa_c.sa_handler = sa_c_handler;
	if (flag == EXECUTING_CMD)
	{
		printf("ioio \n");
		sa_c.sa_handler = sa_c_handler;
	}	
	sigemptyset(&sa_c.sa_mask);
	sa_c.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_c, NULL) == -1)
		return (perror("minishel :"), 0);
	return (1);
}
