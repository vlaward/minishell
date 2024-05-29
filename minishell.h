#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <termios.h>
#include <termcap.h>
#include <sys/ioctl.h>
# include "libft/libft.h"
# include <errno.h>
# include <signal.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# define REDIRECT 1
# define F_NAME_TRIM 1
# define H_DOC_TRIM 2
# define READING_LINE 1
# define EXECUTING_CMD 2
# endif
#endif

typedef struct s_stof
{
	char	*str;
	int		(*func)(char **, int *, int);
}t_stof;

extern int G_sig_catcher;

t_list	*parse(char *line);
int		executeur(t_list *list);
char	*tatu_ferme_tes_guillemets(char *str);
char	**ft_minisplit(char	*str);
char	*get_next_line(int fd);
int		all_good(char *line);
int		verif_tokken(char *line);

//verif_tokken

int		env_handler(char **start_cmd, int *i);
int		guille_handler(char **start_cmd, int *i, int flag);
t_stof	*str_to_func();//on pourait mettre env et guille dedans. Ca serais elegant. redirects le fait deja il faut juste changer le nom

//redirects

int		redirects(char **start_cmd, int *index, t_stof *stofs, int flag);
int		out_handler(char **start_cmd, int *index, int flag);
int		append_handler(char **start_cmd, int *index, int flag);
int		in_handler(char **start_cmd, int *index, int flag);
char	*limit_handler(char *itterand, char *start_cmd);
char	*trim(char **start_cmd, int *index, int flag);
int		here_doc(char **start_cmd);

//signals

int		gere_sig(int flag);