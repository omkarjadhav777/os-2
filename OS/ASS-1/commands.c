#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    pid_t pid;
    int status;
    // Fork a child process for 'cp' command
    pid = fork();
    if (pid < 0)
    { // Fork failed
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    { // Child process
        printf("Child PID: %d\n", getpid());
        // Execute cp command in the child process
        execl("/bin/cp", "cp", "file.txt", "file_copy.txt", NULL);
        // If exec fails, print error
        perror("Exec failed");
        exit(1);
    }
    else
    { // Parent process
        // Wait for the child process to complete
        wait(&status);
        printf("Parent PID: %d\n", getpid());
        printf("File copied successfully.\n");
        printf("Exit status of cp command: %d\n", WEXITSTATUS(status));
        // Fork another child process for 'grep' command
        pid_t grep_pid = fork();
        if (grep_pid < 0)
        { // Fork failed
            perror("Fork failed");
            exit(1);
        }
        else if (grep_pid == 0)
        { // Child process
            printf("Child PID: %d\n", getpid());
            // Execute grep command in the child process
            execl("/bin/grep", "grep", "vinay", "file_copy.txt", NULL);
            // If exec fails, print error
            perror("Exec failed");
            exit(1);
        }
        else
        { // Parent process
            // Wait for the grep process to complete
            wait(&status);
            printf("Parent PID: %d\n", getpid());
            printf("Grep finished.\n");
            printf("Exit status of grep command: %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}