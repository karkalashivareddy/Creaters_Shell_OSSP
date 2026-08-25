#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char command[100];

    printf("Enter a Linux command: ");
    scanf("%99s", command);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process PID: %d\n", getpid());

        execlp(command, command, (char *)NULL);

        perror("exec failed");
        exit(1);
    } else {
        printf("Parent Process PID: %d\n", getpid());
        printf("Child Process PID: %d\n", pid);

        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
