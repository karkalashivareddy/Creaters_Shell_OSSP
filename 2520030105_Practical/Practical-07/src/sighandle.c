/*
 * Practical-07
 * POSIX Signal Handling
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig)
{
    printf("\nCaught SIGINT (signal %d) - Interrupt from keyboard\n", sig);
    printf("Process continuing...\n");
}

void handle_sigterm(int sig)
{
    printf("\nCaught SIGTERM (signal %d) - Termination signal\n", sig);
    printf("Process will exit gracefully.\n");
    exit(0);
}

void handle_sigusr1(int sig)
{
    printf("\nCaught SIGUSR1 (signal %d) - User-defined signal 1\n", sig);
    printf("Received user signal from another process.\n");
}

int main(void)
{
    setbuf(stdout, NULL);

    printf("=== POSIX Signal Handling ===\n\n");

    printf("Process PID: %d\n\n", getpid());

    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR1, handle_sigusr1);

    printf("Signal handlers registered:\n");
    printf("  SIGINT  (2)  -> handle_sigint\n");
    printf("  SIGTERM (15) -> handle_sigterm\n");
    printf("  SIGUSR1 (10) -> handle_sigusr1\n\n");

    printf("Try these commands in another terminal:\n");
    printf("  kill -SIGINT  %d\n", getpid());
    printf("  kill -SIGUSR1 %d\n", getpid());
    printf("  kill -SIGTERM %d\n", getpid());
    printf("\nWaiting for signals... (press Ctrl+C or wait)\n\n");

    while (1)
    {
        pause();
    }

    return 0;
}
