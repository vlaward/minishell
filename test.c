#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include "minishell.h"


#define MAXTERM 1024

int	get_ctrl_d(int pipette[2], int id)
{
	struct termios term;
	char c;

	c = 0;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (read(STDIN_FILENO, &c, 1) != -1)
	{
		if (c == 4)
		{
			if (kill(id, SIGINT) == -1)
				return (perror("kill :"), errno);
			exit(0);
		}
		if (write(pipette[1], &c, 1) == -1)
			return(perror("write :"), errno);
	}
	if (errno)
		perror("read :");
	if (close (pipette[1]) == 1)
		return (perror("dup2"), errno);
	if (close (pipette[0]) == 1)
		return (perror("dup2"), errno);
	return (0);
}

int	ctrl_d_fork()
{
	int	pipette[2];
	int	id;

	 if (pipe(pipette) == -1)
	 	return (perror("pipe :"), errno);
	id = fork();
	if (id < 0)
		return (perror("fork :"), errno);
	if (id)
		return (get_ctrl_d(pipette, id));
	if (dup2(pipette[0], STDIN_FILENO) == -1)
		return (perror("dup2"), errno);
	if (close (pipette[1]) == 1)
		return (perror("dup2"), errno);
	if (close (pipette[0]) == 1)
		return (perror("dup2"), errno);
	return (0);
}


int main()
{
	char *c;

	if (!ctrl_d_fork())
		return (errno);\
	while ((c = readline(">")) && c != NULL)
		write(STDOUT_FILENO, c, ft_strlen(c));
    return 0;
}
