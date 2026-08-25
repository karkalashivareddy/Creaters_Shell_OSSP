/*
 * Practical-02
 * File Copy Using System Calls
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int fd_src, fd_dst;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    ssize_t total_copied = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0)
    {
        perror("Error opening source file");
        return 1;
    }

    fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst < 0)
    {
        perror("Error creating destination file");
        close(fd_src);
        return 1;
    }

    while ((bytes_read = read(fd_src, buffer, BUFFER_SIZE)) > 0)
    {
        char *write_ptr = buffer;
        ssize_t remaining = bytes_read;

        while (remaining > 0)
        {
            bytes_written = write(fd_dst, write_ptr, remaining);
            if (bytes_written < 0)
            {
                perror("Error writing to destination file");
                close(fd_src);
                close(fd_dst);
                return 1;
            }
            write_ptr += bytes_written;
            remaining -= bytes_written;
            total_copied += bytes_written;
        }
    }

    if (bytes_read < 0)
    {
        perror("Error reading from source file");
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    if (close(fd_src) < 0)
    {
        perror("Error closing source file");
        return 1;
    }

    if (close(fd_dst) < 0)
    {
        perror("Error closing destination file");
        return 1;
    }

    printf("File copied successfully.\n");
    printf("Source: %s\n", argv[1]);
    printf("Destination: %s\n", argv[2]);
    printf("Total bytes copied: %zd\n", total_copied);

    return 0;
}
