#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    int fifo_fd;
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    fifo_fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fifo_fd == -1) {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    fd_set read_fds;
    struct timeval timeout;

    // Initialize the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Initialize the set of file descriptors
    FD_ZERO(&read_fds);
    FD_SET(fifo_fd, &read_fds);

    printf("Waiting for data on FIFO for up to 10 seconds...\n");

    // Wait for data to be available
    int activity = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);

    if (activity < 0) {
        perror("Error in select");
        close(fifo_fd);
        exit(EXIT_FAILURE);
    } else if (activity == 0) {
        printf("Timeout: No data within 10 seconds.\n");
    } else {
        if (FD_ISSET(fifo_fd, &read_fds)) {
            // Data is available to read
            ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0'; // Null-terminate the string
                printf("Data received: %s\n", buffer);
            } else {
                perror("Error reading from FIFO");
            }
        }
    }

    close(fifo_fd);
    return 0;
}
