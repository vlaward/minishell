#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libft/libft.h"

typedef struct s_stof
{
	char	*str;
	int		(*func)(t_list *);
}t_stof;

t_list	*parse(char *line);
int	executeur(t_list *list);