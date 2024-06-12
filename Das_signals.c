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

void	sa_c_guillemets_handler(int sig)
{
	struct input_event	ev;
	int fd;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open /dev/uinput");
        return ;
    }

	ev.type = EV_KEY;
	ev.code = KEY_LEFTCTRL;
	ev.value = 1; // Press Left Control key
	write(fd, &ev, sizeof(struct input_event));

	ev.type = EV_KEY;
	ev.code = KEY_D;
	ev.value = 1; // Press letter D
	write(fd, &ev, sizeof(struct input_event));

	ev.type = EV_SYN;
	ev.code = SYN_REPORT;
	ev.value = 0;
	write(fd, &ev, sizeof(struct input_event));

	ev.type = EV_KEY;
	ev.code = KEY_D;
	ev.value = 0; // Release letter D
	write(fd, &ev, sizeof(struct input_event));

	ev.type = EV_KEY;
	ev.code = KEY_LEFTCTRL;
	ev.value = 0; // Release Left Control key
	write(fd, &ev, sizeof(struct input_event));

	ev.type = EV_SYN;
	ev.code = SYN_REPORT;
	ev.value = 0;
	(void)sig;
	// c = EOF;
	// ioctl(ttyslot(), TIOCSTI, &c);
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
