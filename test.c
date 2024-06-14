#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_pipe(char *cmd1[], char *cmd2[]) {
    int pipefd[2]; // Array to hold the two ends of the pipe
    pid_t pid1;//, pid2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to run cmd1
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1 (cmd1)
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close write end of pipe after duplicating
        execve(cmd1[0], cmd1, NULL); // Execute the command
        perror("execve"); // If execve fails
        exit(EXIT_FAILURE); // Exit the child process
    }
	// Child process 2 (cmd2)
	close(pipefd[1]); // Close unused write end
	dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
	close(pipefd[0]); // Close read end of pipe after duplicating
	execve(cmd2[0], cmd2, NULL); // Execute the command
	perror("execve"); // If execve fails
	exit(EXIT_FAILURE); // Exit the child process

    // Parent process
//     close(pipefd[0]); // Close read end of pipe in parent
//     close(pipefd[1]); // Close write end of pipe in parent

//     // Wait for both child processes to finish
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
}

int main() {
    // Example commands
    char *cmd1[] = {"/bin/cat", NULL};
    char *cmd2[] = {"/bin/ls", NULL};

    run_pipe(cmd1, cmd2);

    return 0;
}
