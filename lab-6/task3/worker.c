#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PIPE_NAME "/tmp/my_pipe"

int main() {
    char operator, buffer[20];
    int operand1, operand2, result;
    int pipe_fd;

    // Create the named pipe
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the named pipe for reading
    pipe_fd = open(PIPE_NAME, O_RDONLY);

    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Wait for input from sender
    if (read(pipe_fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Parse the input
    sscanf(buffer, "%c %d %d", &operator, &operand1, &operand2);

    // Perform the calculation
    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        default:
            printf("Invalid operator\n");
            exit(EXIT_FAILURE);
    }

    // Send the result to sender
    if (write(pipe_fd, &result, sizeof(result)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the pipe and exit
    close(pipe_fd);
    exit(EXIT_SUCCESS);
}
