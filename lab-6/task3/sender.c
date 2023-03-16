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

    // Open the named pipe for writing
    pipe_fd = open(PIPE_NAME, O_WRONLY);

    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the input from user
    printf("Enter operator and two operands (separated by spaces): ");
    scanf("%c %d %d", &operator, &operand1, &operand2);

    // Send the input to worker
    sprintf(buffer, "%c %d %d", operator, operand1, operand2);
    if (write(pipe_fd, buffer, strlen(buffer) + 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Wait for result from worker
    if (read(pipe_fd, &result, sizeof(result)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Result: %d\n", result);

    // Close the pipe and exit
    close(pipe_fd);
    exit(EXIT_SUCCESS);
}
