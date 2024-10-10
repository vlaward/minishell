/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrombez <ncrombez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:23:40 by doreetorac        #+#    #+#             */
/*   Updated: 2024/10/10 17:43:01 by ncrombez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
# define FIRST_COMMAND 0
# define NOT_FIRST_COMMAND 1
# define REDIRECT 1
# define REDIRECT 1
# define F_NAME_TRIM 1
# define H_DOC_TRIM 2
# define READING_LINE 1
# define EXECUTING_CMD 2
# define GUILLEMETS 3
# define TTY_SAVED_FD 3
# define MIN_ENV_SIZE 3

typedef struct s_cmd
{
	int		in;
	int		out;
	int		has_pipe;
	int		here_doc;
	int		here_doc_number;
	char	*cmd;
}	t_cmd;

extern int	g_sig_catcher;

typedef int	(*t_builtin)(t_list **, t_list *, char **);

//environement

t_list		*get_env_node(t_list *env, char *str);
t_list		*init_env(char	**env);
char		*ft_getenv(const char *name, t_list *env);

//verif

char		*tatu_ferme_tes_guillemets(char *str);
int			verif_tokken(char *line);

//redirects

int			redirects(char **start_cmd, int *index, t_cmd *cmd, t_list *env);
int			out_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env);
int			append_handler(char **start_cmd, int *index, t_cmd *cm, t_list *e);
int			in_handler(char **start_cmd, int *index, t_cmd *cmd, t_list *env);
char		*limit_handler(char *itterand, char *start_cmd);
char		*trim(char **start_cmd, int *index, int flag, t_list *env);
int			here_doc(char **start_cmd, int *index, t_cmd *cmd, t_list *env);
int			init_redirects(t_list *cmd, t_list *env);
int			cmd_hdoc_only_case(t_cmd *cmd, char **line);
char		*cmd_redirects(t_list *cmd);

//signals

int			gere_sig(int flag);

//builtins
int			ft_env(t_list **redirect, t_list *env, char **cmd);
int			ft_echo(t_list **redirect, t_list *env, char **cmd);
int			ft_pwd(t_list **redirect, t_list *env, char **cmd);
int			ft_exit(t_list **cmd, t_list *env, char **av);
int			ft_export(t_list **redirect, t_list *env, char **av);
int			ft_unset(t_list **redirect, t_list *env, char **av);
int			ft_cd(t_list **redirect, t_list *env, char **av);
t_builtin	ft_builtins(char *str);

//errors

int			big_error(void);
void		export_error(char *str);
void		syntax_error(char *str);
void		guille_error(void);

//memory

void		free_args(char **args);
void		free_cmd(void *afree);

//other

char		**ft_minisplit(char	*str, t_list *env);
char		*get_next_line(int fd);
t_list		*init_cmd(char *line, t_list *env);
int			execute_cmd(char **args, t_list *env);
int			guille_handler(char **start_cmd, int *i, int flag, t_list *env);
int			env_handler(char **start_cmd, int *i, t_list *env);
char		*second_readline(char *str);
int			handle_line(char *line, t_list *env);

#endif
