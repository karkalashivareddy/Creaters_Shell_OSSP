#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;

    printf("Main Process\n");
    printf("PID: %d\n", getpid());

    child1 = fork();

    if (child1 < 0) {
        perror("fork failed");
        return 1;
    }

    if (child1 == 0) {
        printf("\nChild 1\n");
        printf("PID : %d\n", getpid());
        printf("PPID: %d\n", getppid());

        sleep(3);

        printf("Child 1 completed.\n");
        exit(0);
    }

    child2 = fork();

    if (child2 < 0) {
        perror("fork failed");
        return 1;
    }

    if (child2 == 0) {
        printf("\nChild 2\n");
        printf("PID : %d\n", getpid());
        printf("PPID: %d\n", getppid());

        sleep(2);

        printf("Child 2 completed.\n");
        exit(0);
    }

    printf("\nParent Process\n");
    printf("PID     : %d\n", getpid());
    printf("Child 1 : %d\n", child1);
    printf("Child 2 : %d\n", child2);

    wait(NULL);
    wait(NULL);

    printf("\nAll child processes completed.\n");

    return 0;
}
