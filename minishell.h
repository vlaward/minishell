#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft/libft.h"
# include <errno.h>
# include <signal.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif
#endif

typedef struct s_stof
{
	char	*str;
	char		*(*func)(char *, char *);
}t_stof;

t_list	*parse(char *line);
int		executeur(t_list *list);
char	*tatu_ferme_tes_guillemets(char *str);
char	**ft_minisplit(char	*str);
char	*get_next_line(int fd);
t_stof	*str_to_func();
char	*limit_handler(char *itterand, char *start_cmd);
char	*file_name_trim(char **str);
