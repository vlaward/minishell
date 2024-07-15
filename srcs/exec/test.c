#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1
#define MIN_ENV_SIZE 3
#include "../../includes/minishell.h"

char	*ft_getenv(const char *name, t_list *env)
{
	int		size;

	size = ft_strlen(name);
	if (!name || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(name, env->content, size) == 0)
		{
			if (*((char *)env->content + size) == '=')
		 		return (env->content + size + 1);
		}
		env = env->next;
	}
	return (NULL);

}

t_list	*env_from_scratch()
{
	t_list	*ret;
	char	*cwd;
	char	*tmp;

	cwd = (char *)ft_calloc(PATH_MAX, sizeof(char ));
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strjoin("PWD=", cwd)))
		|| !ft_lstlast(ret)->content)
		 return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strdup("SHLVL=1")))
		|| !ft_lstlast(ret)->content)
		return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	tmp = ft_strjoin("_=", cwd);
	if (!tmp)
		return (ft_lstclear(&ret, free), perror("malloc"), NULL);
	if (!ft_lstadd_front(&ret, ft_lstnew(ft_strjoin(tmp, "/./minishell")))
		|| !ft_lstlast(ret)->content)
		return (ft_lstclear(&ret, free), free(tmp), perror("malloc"), NULL);
	return (ret);
	}

char	*shlvl_increment(char	*env)
{
	char	*nbr;
	char	*ret;

	nbr = ft_itoa(ft_atoi(env + 6) + 1);
	if (!nbr)
		return (NULL);
	ret = ft_strjoin("SHLVL=", nbr);
	return (free(nbr), ret);
}


t_list	*init_env(char **env)
{
	t_list	*ret;

	if (!env || !*env)
		return (env_from_scratch());
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 5) == 0)
			ft_lstadd_front(&ret, ft_lstnew(shlvl_increment(*(env++))));
		else
			ft_lstadd_front(&ret, ft_lstnew(ft_strdup(*(env++))));
		if (!ft_lstlast(ret)->content)
			return (ft_lstclear(&ret, free), perror("malloc"), NULL);//<===============================FREE THE FUCKING TABLE DON'T YOU FORGET U SUCKER (of course use ret 'caus you ain't dumb)
	}
	return (ret);
}

int	main()
{
	char *str = "sale pute";

	switch (str)
	{
		case ft_strcmp("sale pute", str) == 0:
			printf("AHA\n");
		default:
			printf("aaaaww.....\n");
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_list	*newenv;
// 	t_list	*tmp;

// 	newenv = init_env(env);
// 	if (!newenv)
// 		return (printf("je m'en doute,  reste a savoir pourquoi\n"), 1);
// 	printf("voici :\"SHLVL\" qui est egal a \"%s\"\n", ft_getenv("SHLVL", newenv));
// 	while (newenv != NULL)
// 	{
// 		tmp = newenv->next;
// 		printf("%s\n", (char *)newenv->content);
// 		ft_lstdelone(newenv, &free);
// 		newenv = tmp;
// 	}
// 	return (0);
// }


// void write_here_doc_content(int fd) {
//     const char *here_doc = "Here document content\n";
//     write(fd, here_doc, strlen(here_doc));
// }

// int main() {
//     int pipe_ls[2];
//     int pipe_combined[2];
//     pid_t pid_ls, pid_cat, pid_combine;

//     // Create pipes
//     if (pipe(pipe_ls) == -1 || pipe(pipe_combined) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Fork the first child to execute 'ls'
//     pid_ls = fork();
//     if (pid_ls == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid_ls == 0) {
//         // Child 1: 'ls'
//         close(pipe_ls[READ_END]); // Close the read end of the ls pipe
//         dup2(pipe_ls[WRITE_END], STDOUT_FILENO); // Redirect stdout to the write end of the ls pipe
//         close(pipe_ls[WRITE_END]);
//         close(pipe_combined[READ_END]);
//         close(pipe_combined[WRITE_END]);

//         execlp("./test.sh", "./test.sh", NULL); // Execute 'ls'
//         perror("execlp");
//         exit(EXIT_FAILURE);
//     }

//     // Fork a second child to combine the output of 'ls' and the here-doc content
//     pid_combine = fork();
//     if (pid_combine == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid_combine == 0) {
//         // Child 2: combine
//         close(pipe_ls[WRITE_END]); // Close the write end of the ls pipe
//         close(pipe_combined[READ_END]); // Close the read end of the combined pipe

//         // Read from ls pipe and write to combined pipe
//         char buffer[1024];
//         ssize_t bytes_read;
//         while ((bytes_read = read(pipe_ls[READ_END], buffer, sizeof(buffer))) > 0) {
//             write(pipe_combined[WRITE_END], buffer, bytes_read);
//         }

//         // Write the here-doc content to the combined pipe
//         write_here_doc_content(pipe_combined[WRITE_END]);

//         close(pipe_ls[READ_END]);
//         close(pipe_combined[WRITE_END]);
//         exit(EXIT_SUCCESS);
//     }

//     // Fork the third child to execute 'cat'
//     pid_cat = fork();
//     if (pid_cat == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid_cat == 0) {
//         // Child 3: 'cat'
//         close(pipe_combined[WRITE_END]); // Close the write end of the combined pipe
//         dup2(pipe_combined[READ_END], STDIN_FILENO); // Redirect stdin to the read end of the combined pipe
//         close(pipe_combined[READ_END]);
//         close(pipe_ls[READ_END]);
//         close(pipe_ls[WRITE_END]);

//         execlp("cat", "cat", NULL); // Execute 'cat'
//         perror("execlp");
//         exit(EXIT_FAILURE);
//     }

//     // Parent process
//     close(pipe_ls[READ_END]);
//     close(pipe_ls[WRITE_END]);
//     close(pipe_combined[READ_END]);
//     close(pipe_combined[WRITE_END]);

//     // Wait for all children to complete
//     waitpid(pid_ls, NULL, 0);
//     waitpid(pid_combine, NULL, 0);
//     waitpid(pid_cat, NULL, 0);

//     return 0;
// }
