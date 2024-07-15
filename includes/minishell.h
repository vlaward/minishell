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
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include <linux/uinput.h>
# include <errno.h>
# include <signal.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif
#ifndef PATH_MAX
# define PATH_MAX 4096
# endif
#define FIRST_COMMAND 0
#define NOT_FIRST_COMMAND 1
#define REDIRECT 1
# define REDIRECT 1
# define F_NAME_TRIM 1
# define H_DOC_TRIM 2
# define READING_LINE 1
# define EXECUTING_CMD 2
# define GUILLEMETS 3
# define TTY_SAVED_FD 3
#endif

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

extern int G_sig_catcher;

extern char **G_env;

t_list *init_env(char	**env);
char	*tatu_ferme_tes_guillemets(char *str);
char	**ft_minisplit(char	*str);
char	*get_next_line(int fd);
int		all_good(char *line, t_list *env);
int		verif_tokken(char *line);

//verif_tokken

int		env_handler(char **start_cmd, int *i);
int		guille_handler(char **start_cmd, int *i, int flag);

//redirects

int		redirects(char **start_cmd, int *index, int flag, t_list *env);
int		out_handler(char **start_cmd, int *index, int flag, t_list *env);
int		append_handler(char **start_cmd, int *index, int flag, t_list *env);
int		in_handler(char **start_cmd, int *index, int flag, t_list *env);
char	*limit_handler(char *itterand, char *start_cmd);
char	*trim(char **start_cmd, int *index, int flag, t_list *env);
int		here_doc(char **start_cmd, int *index, int flag, t_list *env);

//signals

int		gere_sig(int flag);

//builtins
void	ft_env(void);
void	ft_echo(char **av);
void	ft_builtins(char **av);
void	ft_pwd(void);
void	ft_exit(char **av);
void	ft_export(char **av);

int	ft_is_builtins(char *av);

//list

t_env	*__lstnew(void *content);
void	__lstadd_back(t_env **lst, t_env *new);
t_env	*__lstlast(t_env *lst);
char	*ft_get_value(char *str);
char	*ft_get_key(char *str);
t_env	*__tab_lst(char **env);
