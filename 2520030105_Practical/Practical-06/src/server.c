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
#include <errno.h>

#define FIFO_SERVER "/tmp/server_fifo"
#define FIFO_CLIENT "/tmp/client_fifo"
#define BUFFER_SIZE 256

int main(void)
{
    int fd_server, fd_client;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    setbuf(stdout, NULL);

    printf("=== Server - Named Pipe Communication ===\n\n");

    if (mkfifo(FIFO_SERVER, 0666) < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo server_fifo failed");
            return 1;
        }
    }

    if (mkfifo(FIFO_CLIENT, 0666) < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo client_fifo failed");
            return 1;
        }
    }

    printf("FIFOs created: %s and %s\n", FIFO_SERVER, FIFO_CLIENT);
    printf("Server waiting for client connection...\n");

    fd_server = open(FIFO_SERVER, O_RDONLY);
    if (fd_server < 0)
    {
        perror("open server_fifo failed");
        return 1;
    }

    printf("Client connected!\n\n");

    while (1)
    {
        bytes_read = read(fd_server, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0)
            break;

        buffer[bytes_read] = '\0';
        printf("Server received: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            printf("Client sent exit command. Server shutting down.\n");
            break;
        }

        fd_client = open(FIFO_CLIENT, O_WRONLY);
        if (fd_client < 0)
        {
            perror("open client_fifo failed");
            continue;
        }

        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "Server processed: '%s'", buffer);
        write(fd_client, response, strlen(response) + 1);
        close(fd_client);

        printf("Server sent response.\n\n");
    }

    close(fd_server);

    unlink(FIFO_SERVER);
    unlink(FIFO_CLIENT);

    printf("FIFOs removed. Server exiting.\n");

    return 0;
}
