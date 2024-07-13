#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../../includes/minishell.h"

#define READ_END 0
#define WRITE_END 1
#define MIN_ENV_SIZE 3

char	**env_from_scratch()//Changer les free pars les nouvelles fonctrionsa de la libft que je vais rajkouter. rajouter les perror
{
	char	**ret;
	char	*cwd;
	char	*tmp;

	cwd = (char *)ft_calloc(PATH_MAX, sizeof(char ));
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	ret = (char**)ft_calloc(MIN_ENV_SIZE + 1, sizeof(char *));
	if (!ret)
		return (perror("malloc"), NULL);
	ret[3] = NULL;
	ret[0] = ft_strjoin("PWD=", cwd);
	if (!ret[0])
		return(free(ret[1]), free(ret), free(cwd), NULL) ;
	ret[1] = ft_strdup("SHLVL=1");
	if (!ret[1])
		return(free(ret), free(cwd), NULL) ;
	tmp = ft_strjoin("_=", cwd);
	if (!tmp)
		return(free(ret[1]), free(ret[0]), free(ret), free(cwd), NULL) ;
	ret[2] = ft_strjoin(tmp, "/./minishell");
	if (!ret[2])
		return(free(ret[1]), free(ret[0]), free(ret), free(cwd), free(tmp), NULL);//trop long mais ca reduiras avec les nouveau free
	return (ret);
	}

char	*shlvl_increment(char	*env)//J'aime pas faire de si petites fonctyions mais je crois que c'est plus clair comme ca
{
	char	*nbr;
	char	*ret;

	nbr = ft_itoa(ft_atoi(env + 6) + 1);
	if (!nbr)
		return (NULL);
	ret = ft_strjoin("SHLVL=", nbr);
	return (free(nbr), ret);
}


char **init_env(char **env)//changer le compteur de "size" du tableau pour une fonction de la libft que je ais rajouter 
{
	char	**ret;
	char	**tmp;

	if (!env || !*env)
		return (env_from_scratch());
	ret = (char**)ft_calloc(ft_table_size(env) + 1, sizeof(char *));
	if (!ret)
	 	return (perror("malloc"), NULL);
	tmp = ret;
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 5) == 0)
			*(ret) = shlvl_increment(*(env++));
		else
			*(ret) = ft_strdup(*(env++));
		if (!*(ret++))
			return (perror("malloc"), NULL);//<===============================FREE THE FUCKING TABLE DON'T YOU FORGET U SUCKER (of course use tmp 'caus you ain't dumb)
	}
	*ret = NULL;//don';t know if it's uselfull knowing full ass I used calloc that init evrything at 0. Still think it's usefull
	return (tmp);
}

int	main(int ac, char **av, char **env)
{
	char	**newenv;
	char	**tmp;

	newenv = init_env(env);
	if (!newenv)
		return (printf("je m'en doute,  reste a savoir pourquoi\n"), 1);
	tmp = newenv;
	while (*newenv != NULL)
		(printf("%s\n", *newenv), free(*(newenv++)));
	free(tmp);
	return (0);
}


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
