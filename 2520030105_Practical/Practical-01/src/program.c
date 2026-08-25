/*
 * Practical-01
 * Process Creation and Command Execution
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int parse_command(char *input, char *args[])
{
    int argc = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && argc < MAX_ARGS - 1)
    {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;
    return argc;
}

int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    pid_t pid;

    setbuf(stdout, NULL);

    printf("Enter a Linux command: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Error reading input.\n");
        return 1;
    }

    int argc = parse_command(input, args);
    if (argc == 0)
    {
        printf("No command entered.\n");
        return 1;
    }

    printf("Parent process started.\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild process created.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID from child: %d\n", getppid());
        printf("Child executing command using exec().\n");

        execvp(args[0], args);

        perror("exec failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nParent waiting for child...\n");

        wait(NULL);

        printf("Child process completed.\n");
        printf("Parent process exiting.\n");
    }

    return 0;
}
