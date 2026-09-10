/*
 * Practical-06
 * Client Server Communication using Named Pipes (FIFO)
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_SERVER "/tmp/server_fifo"
#define FIFO_CLIENT "/tmp/client_fifo"
#define BUFFER_SIZE 256

int main(void)
{
    int fd_server, fd_client;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    ssize_t bytes_read;

    setbuf(stdout, NULL);

    printf("=== Client - Named Pipe Communication ===\n\n");

    printf("Connecting to server...\n");

    fd_server = open(FIFO_SERVER, O_WRONLY);
    if (fd_server < 0)
    {
        perror("open server_fifo failed");
        printf("Make sure server is running first.\n");
        return 1;
    }

    fd_client = open(FIFO_CLIENT, O_RDONLY);
    if (fd_client < 0)
    {
        perror("open client_fifo failed");
        close(fd_server);
        return 1;
    }

    printf("Connected to server!\n\n");

    while (1)
    {
        printf("Enter message (or 'exit' to quit): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        write(fd_server, input, strlen(input) + 1);

        if (strcmp(input, "exit") == 0)
        {
            printf("Disconnected from server.\n");
            break;
        }

        bytes_read = read(fd_client, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            printf("Server response: %s\n\n", buffer);
        }
    }

    close(fd_server);
    close(fd_client);

    return 0;
}
