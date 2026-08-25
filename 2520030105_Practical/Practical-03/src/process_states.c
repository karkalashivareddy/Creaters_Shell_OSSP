/*
 * Practical-03
 * Process Creation and State Transitions
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

void read_proc_stat(pid_t pid)
{
    char path[64];
    FILE *fp;
    int rpid, ppid;
    char state;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("    Cannot read /proc/%d/stat\n", pid);
        return;
    }

    if (fscanf(fp, "%d %*s %c %d", &rpid, &state, &ppid) == 3)
    {
        printf("    /proc/%d/stat -> PID=%d State=%c PPID=%d\n", pid, rpid, state, ppid);
    }
    fclose(fp);
}

void read_proc_status(pid_t pid)
{
    char path[64];
    char line[256];
    FILE *fp;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("    Cannot read /proc/%d/status\n", pid);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "Pid:", 4) == 0 ||
            strncmp(line, "PPid:", 5) == 0 ||
            strncmp(line, "Name:", 5) == 0)
        {
            line[strcspn(line, "\n")] = '\0';
            printf("    %s\n", line);
        }
    }
    fclose(fp);
}

int main(void)
{
    pid_t pid;
    int status;

    setbuf(stdout, NULL);

    printf("=== Process State Transitions Experiment ===\n\n");

    printf("STAGE 1: Parent process started.\n");
    printf("  Parent PID:  %d\n", getpid());
    printf("  Parent PPID: %d\n", getppid());
    read_proc_stat(getpid());
    read_proc_status(getpid());

    printf("\nSTAGE 2: Forking child process...\n");
    fflush(stdout);
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        pid_t my_pid = getpid();
        pid_t my_ppid = getppid();

        printf("\nSTAGE 3: Child process created.\n");
        printf("  Child PID:  %d\n", my_pid);
        printf("  Child PPID: %d\n", my_ppid);
        read_proc_stat(my_pid);
        read_proc_status(my_pid);
        fflush(stdout);

        printf("\nSTAGE 4: Child entering sleep (waiting state)...\n");
        fflush(stdout);
        sleep(10);

        read_proc_stat(my_pid);
        read_proc_status(my_pid);
        fflush(stdout);

        printf("\nSTAGE 5: Child performing computation (running state)...\n");
        {
            volatile long i;
            long sum = 0;
            for (i = 0; i < 10000000; i++)
            {
                sum += i;
            }
            printf("  Computation result: %ld\n", sum);
        }
        read_proc_stat(my_pid);
        fflush(stdout);

        printf("\nSTAGE 6: Child about to exit.\n");
        read_proc_stat(my_pid);
        fflush(stdout);

        exit(0);
    }
    else
    {
        printf("\nSTAGE 3: Parent created child (PID=%d).\n", pid);
        read_proc_stat(getpid());
        fflush(stdout);

        printf("\nSTAGE 4: Parent waiting for child...\n");
        read_proc_stat(getpid());
        fflush(stdout);

        waitpid(pid, &status, 0);

        printf("\nSTAGE 6: Child finished. Parent resumed.\n");
        if (WIFEXITED(status))
        {
            printf("  Child exited with status: %d\n", WEXITSTATUS(status));
        }
        read_proc_stat(getpid());
        read_proc_status(getpid());
        fflush(stdout);

        printf("\nSTAGE 7: Parent process exiting.\n");
    }

    return 0;
}
