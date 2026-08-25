/*
 * Skill-01
 * fork() Demo - Process Abstraction and Parent-Child Relationship
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

    setbuf(stdout, NULL);

    printf("=== fork() Demonstration ===\n\n");
    printf("Main process PID: %d\n", getpid());
    printf("Main process PPID: %d\n\n", getppid());

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork 1 failed");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("  [Child 1] PID=%d PPID=%d\n", getpid(), getppid());
        printf("  [Child 1] I am a child process created by fork().\n");
        sleep(2);
        printf("  [Child 1] Exiting.\n");
        exit(1);
    }
    else
    {
        printf("  [Parent] Created child 1 with PID=%d\n", pid1);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork 2 failed");
        return 1;
    }

    if (pid2 == 0)
    {
        printf("  [Child 2] PID=%d PPID=%d\n", getpid(), getppid());
        printf("  [Child 2] I am another child process.\n");
        sleep(1);
        printf("  [Child 2] Exiting.\n");
        exit(2);
    }
    else
    {
        printf("  [Parent] Created child 2 with PID=%d\n", pid2);
    }

    printf("\n[Parent] Waiting for both children...\n");

    int status;
    pid_t finished;

    finished = waitpid(pid1, &status, 0);
    if (WIFEXITED(status))
    {
        printf("[Parent] Child 1 (PID=%d) exited with status %d\n",
               finished, WEXITSTATUS(status));
    }

    finished = waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
    {
        printf("[Parent] Child 2 (PID=%d) exited with status %d\n",
               finished, WEXITSTATUS(status));
    }

    printf("\n[Parent] All children finished. Exiting.\n");
    return 0;
}
