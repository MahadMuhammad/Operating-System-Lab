#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO1 "factorial_fifo"
#define FIFO2 "square_fifo"

int main() {
    int num, factorial, square;
    int fifo1_fd, fifo2_fd;

    // create named pipes
    if (mkfifo(FIFO1, 0666) == -1 || mkfifo(FIFO2, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // first child process - calculate factorial
        fifo1_fd = open(FIFO1, O_RDONLY);
        read(fifo1_fd, &num, sizeof(int));
        factorial = 1;
        for (int i = 2; i <= num; i++) {
            factorial *= i;
        }
        fifo2_fd = open(FIFO2, O_WRONLY);
        write(fifo2_fd, &factorial, sizeof(int));
        close(fifo1_fd);
        close(fifo2_fd);
        exit(EXIT_SUCCESS);
    } else {
        pid_t pid2 = fork();

        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // second child process - calculate square
            fifo1_fd = open(FIFO1, O_RDONLY);
            read(fifo1_fd, &num, sizeof(int));
            square = num * num;
            fifo2_fd = open(FIFO2, O_WRONLY);
            write(fifo2_fd, &square, sizeof(int));
            close(fifo1_fd);
            close(fifo2_fd);
            exit(EXIT_SUCCESS);
        } else {
            // parent process - get input from user, and wait for children
            fifo1_fd = open(FIFO1, O_WRONLY);
            fifo2_fd = open(FIFO2, O_RDONLY);
            printf("Enter a number: ");
            scanf("%d", &num);
            write(fifo1_fd, &num, sizeof(int));
            close(fifo1_fd);
            wait(NULL);
            wait(NULL);
            read(fifo2_fd, &factorial, sizeof(int));
            read(fifo2_fd, &square, sizeof(int));
            close(fifo2_fd);
            printf("Factorial of %d is %d\n", num, factorial);
            printf("Square of %d is %d\n", num, square);
        }
    }

    // remove named pipes
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
