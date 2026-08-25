#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char source[100];
    char destination[100];
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    printf("Enter source file name: ");
    scanf("%99s", source);

    printf("Enter destination file name: ");
    scanf("%99s", destination);

    int source_fd = open(source, O_RDONLY);

    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    int destination_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destination_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytesWritten = write(destination_fd, buffer, bytesRead);

        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(source_fd);
            close(destination_fd);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading source file");
    }

    close(source_fd);
    close(destination_fd);

    printf("File copied successfully.\n");

    return 0;
}
