#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t p;
    int fd[2]; // Array to hold file descriptors for the pipe

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    p = fork(); // Create a child process

    if (p > 0) { // Parent process
        close(fd[0]);               // Close the read end of the pipe (parent only writes)
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the pipe's write end
        close(fd[1]);               // Close the write end (now handled by STDOUT)


        execlp("ls", "ls", "--color=never", NULL);   // Execute "ls"
        perror("execlp failed");    // If execlp fails, print an error
        exit(EXIT_FAILURE);


    } else if (p == 0) { // Child process
        close(fd[1]);               // Close the write end of the pipe (child only reads)
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin to the pipe's read end
        close(fd[0]);               // Close the read end (now handled by STDIN)

        execlp("wc", "wc", "-l", NULL); // Execute "wc -l"
        perror("execlp failed");    // If execlp fails, print an error
        exit(EXIT_FAILURE);
    } else { // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    wait(NULL);


    // Ensure the parent waits for the child to finish

    return 0;
}
