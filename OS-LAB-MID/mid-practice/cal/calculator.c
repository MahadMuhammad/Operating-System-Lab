#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char *fifo_name = "/tmp/calculator_fifo";
    int fd;

    // Create the FIFO if it doesn't exist
    mkfifo(fifo_name, 0666);

    while(1) {
        // Open the FIFO for reading
        fd = open(fifo_name, O_RDONLY);
        if(fd == -1) {
            perror("open");
            return 1;
        }

        // Read the message from the FIFO
        char message[64];
        read(fd, message, 64);

        // Parse the message
        char operator[2];
        int operand1, operand2;
        sscanf(message, "%s %d %d", operator, &operand1, &operand2);

        // Calculate the result
        int result;
        if(strcmp(operator, "+") == 0) {
            result = operand1 + operand2;
        } else if(strcmp(operator, "-") == 0) {
            result = operand1 - operand2;
        } else if(strcmp(operator, "*") == 0) {
            result = operand1 * operand2;
        } else if(strcmp(operator, "/") == 0) {
            result = operand1 / operand2;
        } else {
            result = 0;
        }

        // Close the FIFO
        close(fd);

        // Open the FIFO for writing
        fd = open(fifo_name, O_WRONLY);
        if(fd == -1) {
            perror("open");
            return 1;
        }

        // Write the result to the FIFO
        char result_message[64];
        sprintf(result_message, "%d", result);
        write(fd, result_message, strlen(result_message) + 1);

        // Close the FIFO
        close(fd);
    }

    return 0;
}
