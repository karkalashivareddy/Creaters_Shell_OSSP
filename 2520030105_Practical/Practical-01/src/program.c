/*
 * Practical-01
 * Process Creation and Command Execution
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    setbuf(stdout, NULL);

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
        printf("Child executing 'ls -l' using exec().\n");

        execlp("ls", "ls", "-l", (char *)NULL);

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
