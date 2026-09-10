/*
 * Practical-04
 * Zombie Process
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

    printf("=== Zombie Process Demonstration ===\n\n");

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
        printf("Child PPID: %d\n", getppid());
        printf("Child exiting immediately...\n");
        exit(0);
    }
    else
    {
        printf("\nParent created child with PID: %d\n", pid);
        printf("Child is now a zombie (Z state) because parent did not call wait().\n");
        printf("Run 'ps -l' in another terminal to see the zombie process.\n");
        printf("Parent sleeping for 15 seconds...\n");
        printf("Check 'ps -l | grep defunct' before parent exits.\n\n");

        sleep(15);

        printf("Parent now calling wait() to collect child exit status.\n");
        wait(NULL);
        printf("Zombie cleaned up. Parent exiting.\n");
    }

    return 0;
}
