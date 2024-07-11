#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1
#include "../../includes/minishell.h"

int		taille_env(char	**env)
{
	int	i;

	if (!env)
		return (-1);
	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	**env_from_scratch()
{
	char	**ret;
	char	*pwd;

	pwd = (char*)malloc(PATH_MAX * sizeof(char));
	getcwd(pwd, PATH_MAX * sizeof(char));
	if (!pwd)
		return (perror("malloc"), NULL);
	ret = (char**)malloc(4 * sizeof(char*));
	if (!ret)
		return (free(pwd), perror("malloc"), NULL);
	ret[0] = ft_strjoin("PWD=", pwd);
	ret[1] = ft_strdup("SHLVL=1");
	ret[2] = ft_strjoin(ret[0], "/./minishell");
	return (free(pwd), ret);
}

int	set_env(char **env)
{
	char	*tmp;

	if (!env || !*env)
		return (0);
	if (ft_strncmp(*env, "SHLVL=", 6) == 0)
	{
		tmp = ft_itoa(ft_atoi(*env + 6) + 1);
		if (!tmp)
			return (0);
		*(*env + 6) = '\0';
		*env = ft_strjoin_n_free(*env, tmp);
		if (!*env)
			return (0);
	}
	return (1);
}

char	**init_env(char	**env)
{
	char	**ret;
	int		size;

	size = taille_env(env);
	if (size <= 0)
		return (env_from_scratch());
	ret = (char**)malloc((size + 1) * sizeof(char*));//initialiser a 0 ?
	size = 0;
	if (!ret)
		return (perror("malloc"), NULL);
	while (*env)
	{
		ret[size] = ft_strdup(*env);
		if (!set_env(&ret[size++]))
		{
			while (--size >= 0)
				free(ret[size]);
			free(ret);
			return (perror("malloc"), NULL);
		}
		env++;
	}
	ret[size] = NULL;
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	char **newenv;
	int		i;

	i = 0;
	newenv = init_env(env);
	if (!newenv)
		return (printf("ah bon bah d'acccord\n"), 0);
	while (newenv[i])
		printf("%s\n", newenv[i]) ,free(newenv[i++]);
	free(newenv);
	return (1);
}
/*
void write_here_doc_content(int fd) {
    const char *here_doc = "Here document content\n";
    write(fd, here_doc, strlen(here_doc));
}

int main() {
    int pipe_ls[2];
    int pipe_combined[2];
    pid_t pid_ls, pid_cat, pid_combine;

    // Create pipes
    if (pipe(pipe_ls) == -1 || pipe(pipe_combined) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to execute 'ls'
    pid_ls = fork();
    if (pid_ls == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_ls == 0) {
        // Child 1: 'ls'
        close(pipe_ls[READ_END]); // Close the read end of the ls pipe
        dup2(pipe_ls[WRITE_END], STDOUT_FILENO); // Redirect stdout to the write end of the ls pipe
        close(pipe_ls[WRITE_END]);
        close(pipe_combined[READ_END]);
        close(pipe_combined[WRITE_END]);

        execlp("./test.sh", "./test.sh", NULL); // Execute 'ls'
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork a second child to combine the output of 'ls' and the here-doc content
    pid_combine = fork();
    if (pid_combine == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_combine == 0) {
        // Child 2: combine
        close(pipe_ls[WRITE_END]); // Close the write end of the ls pipe
        close(pipe_combined[READ_END]); // Close the read end of the combined pipe

        // Read from ls pipe and write to combined pipe
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_ls[READ_END], buffer, sizeof(buffer))) > 0) {
            write(pipe_combined[WRITE_END], buffer, bytes_read);
        }

        // Write the here-doc content to the combined pipe
        write_here_doc_content(pipe_combined[WRITE_END]);

        close(pipe_ls[READ_END]);
        close(pipe_combined[WRITE_END]);
        exit(EXIT_SUCCESS);
    }

    // Fork the third child to execute 'cat'
    pid_cat = fork();
    if (pid_cat == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_cat == 0) {
        // Child 3: 'cat'
        close(pipe_combined[WRITE_END]); // Close the write end of the combined pipe
        dup2(pipe_combined[READ_END], STDIN_FILENO); // Redirect stdin to the read end of the combined pipe
        close(pipe_combined[READ_END]);
        close(pipe_ls[READ_END]);
        close(pipe_ls[WRITE_END]);

        execlp("cat", "cat", NULL); // Execute 'cat'
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipe_ls[READ_END]);
    close(pipe_ls[WRITE_END]);
    close(pipe_combined[READ_END]);
    close(pipe_combined[WRITE_END]);

    // Wait for all children to complete
    waitpid(pid_ls, NULL, 0);
    waitpid(pid_combine, NULL, 0);
    waitpid(pid_cat, NULL, 0);

    return 0;
}
*/
