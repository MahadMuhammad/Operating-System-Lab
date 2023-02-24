#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num, factorial, square;
    int fd1[2], fd2[2], fd3[2], fd4[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1 || pipe(fd4) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // first child process - calculate factorial
        close(fd1[1]);
        read(fd1[0], &num, sizeof(int));
        close(fd1[0]);
        factorial = 1;
        for (int i = 2; i <= num; i++) {
            factorial *= i;
        }
        close(fd3[0]);
        write(fd3[1], &factorial, sizeof(int));
        close(fd3[1]);
        exit(EXIT_SUCCESS);
    } else {
        pid_t pid2 = fork();

        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // second child process - calculate square
            close(fd2[1]);  // close write end of pipe 2
            read(fd2[0], &num, sizeof(int));
            close(fd2[0]);
            square = num * num;
            close(fd4[0]);
            write(fd4[1], &square, sizeof(int));
            close(fd4[1]);
            exit(EXIT_SUCCESS);
        } else {
            // parent process - get input from user, and wait for children
            close(fd1[0]);
            close(fd2[0]);
            close(fd3[1]);
            close(fd4[1]);
            printf("Enter a number: ");
            scanf("%d", &num);
            write(fd1[1], &num, sizeof(int));
            write(fd2[1], &num, sizeof(int));
            close(fd1[1]);
            close(fd2[1]);
            wait(NULL);
            wait(NULL);
            read(fd3[0], &factorial, sizeof(int));
            read(fd4[0], &square, sizeof(int));
            close(fd3[0]);
            close(fd4[0]);
            printf("Factorial of %d is %d\n", num, factorial);
            printf("Square of %d is %d\n", num, square);
        }
    }

    return 0;
}
