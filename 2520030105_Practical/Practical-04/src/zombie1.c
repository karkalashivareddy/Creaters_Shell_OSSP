/*
 * Practical-04
 * Zombie Process (Variation - Multiple Children)
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
    pid_t pid1, pid2;
    int status;

    setbuf(stdout, NULL);

    printf("=== Zombie Process - Multiple Children ===\n\n");

    printf("Parent PID: %d\n", getpid());

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("Child 1 (PID: %d) exiting immediately.\n", getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid2 == 0)
    {
        printf("Child 2 (PID: %d) exiting immediately.\n", getpid());
        exit(2);
    }

    printf("Parent created two children: PID %d and PID %d\n", pid1, pid2);
    printf("Both children have exited. They are zombies now.\n");
    printf("Run 'ps -l' in another terminal to see zombie (Z) state.\n\n");

    sleep(10);

    printf("Parent collecting child 1 exit status...\n");
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status))
    {
        printf("  Child 1 exited with status: %d\n", WEXITSTATUS(status));
    }

    printf("Parent collecting child 2 exit status...\n");
    waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
    {
        printf("  Child 2 exited with status: %d\n", WEXITSTATUS(status));
    }

    printf("\nAll zombies cleaned up. Parent exiting.\n");

    return 0;
}
