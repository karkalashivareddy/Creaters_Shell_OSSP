#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent Process\n");
    printf("PID  : %d\n", getpid());
    printf("PPID : %d\n", getppid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("\nChild Process\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());

        printf("Child is executing...\n");

        execlp("ls", "ls", "-l", (char *)NULL);

        perror("exec failed");
        exit(1);
    }
    else {
        printf("\nParent created child.\n");
        printf("Child PID: %d\n", pid);

        wait(NULL);

        printf("Child execution completed.\n");
    }

    return 0;
}
