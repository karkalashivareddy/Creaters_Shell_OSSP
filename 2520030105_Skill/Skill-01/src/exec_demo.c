/*
 * Skill-01
 * exec() Family Demo - Command Execution
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

    printf("=== exec() Family Demonstration ===\n\n");
    printf("Main process PID: %d\n\n", getpid());

    printf("--- Test 1: execlp() running 'ls -l' ---\n");
    pid = fork();
    if (pid == 0)
    {
        printf("  [Child PID=%d] Calling execlp(\"ls\", \"ls\", \"-l\")...\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("  [Parent] Child finished.\n\n");
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    printf("--- Test 2: execvp() running 'uname -a' ---\n");
    pid = fork();
    if (pid == 0)
    {
        char *args[] = {"uname", "-a", NULL};
        printf("  [Child PID=%d] Calling execvp(\"uname\", args)...\n", getpid());
        execvp("uname", args);
        perror("execvp failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("  [Parent] Child finished.\n\n");
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    printf("--- Test 3: execl() running 'date' ---\n");
    pid = fork();
    if (pid == 0)
    {
        printf("  [Child PID=%d] Calling execl(\"/bin/date\", \"date\")...\n", getpid());
        execl("/bin/date", "date", (char *)NULL);
        perror("execl failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("  [Parent] Child finished.\n\n");
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    printf("=== All exec() demos complete ===\n");
    return 0;
}
