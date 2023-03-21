#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 4) {
        printf("Usage: %s <operator> <operand> <operand>\n", argv[0]);
        return 1;
    }

    char *fifo_name = "/tmp/calculator_fifo";
    int fd;

    // Open the FIFO for writing
    fd = open(fifo_name, O_WRONLY);
    if(fd == -1) {
        perror("open");
        return 1;
    }

    // Construct the message to send
    char message[64];
    sprintf(message, "%s %s %s", argv[1], argv[2], argv[3]);

    // Write the message to the FIFO
    write(fd, message, strlen(message) + 1);

    // Close the FIFO
    close(fd);

    // Open the FIFO for reading
    fd = open(fifo_name, O_RDONLY);
    if(fd == -1) {
        perror("open");
        return 1;
    }

    // Read the result from the FIFO
    char result[64];
    read(fd, result, 64);

    // Display the result
    printf("Result: %s\n", result);

    // Close the FIFO
    close(fd);

    return 0;
}
