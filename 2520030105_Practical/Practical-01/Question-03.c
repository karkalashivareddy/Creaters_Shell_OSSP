#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent Process Started\n");
    printf("Parent PID  : %d\n", getpid());
    printf("Parent PPID : %d\n", getppid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("\nChild Process Started\n");
        printf("Child PID  : %d\n", getpid());
        printf("Child PPID : %d\n", getppid());

        printf("Child is running...\n");

        sleep(5);

        printf("Child is terminating...\n");

        exit(0);
    } 
    else {
        printf("\nParent is waiting for child...\n");

        sleep(2);

        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        wait(NULL);

        printf("Child process has terminated.\n");
        printf("Parent process completed.\n");
    }

    return 0;
}
