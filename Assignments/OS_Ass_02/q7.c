/*
    Muhammad Mahad 21L-6195

    Write a program for inter-process communication among three processes using pipes.
    In which,one process is Parent which has two child processes.

    1) Parent process gets a number from the user.
    2) First child reads the number from the pipe and calculates the factorial.
    3) Similarly, the second child reads the number from pipe and calculates the square of that number.
    4) In the end, the Parent process read the output from the pipe and display it.
    
    prototype: 
    
    1) int pipe(int fd[2]);
            return value: 0 on success, -1 on error
    2) write(int fd, const void *buf, size_t count);
            return value: number of bytes written on success, -1 on error
    3) read(int fd, void *buf, size_t count);
            return value: number of bytes read on success, -1 on error
    4) waitpid(pid_t pid, int *status, int options);
            options: WNOHANG, WUNTRACED
            return value: pid of child process on success, -1 on error


                      P1        (Get number from user)
                     /  \
                    P1  C1    
                   /      \
                 P1        C1   (C1 read from parent and calculate factorial)
                /  \        \
               P1   C2       C1 (C2 read from parent and calculate square) 
*/

#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // exit()
#include <unistd.h>     // fork(), pipe()
#include <sys/wait.h>   // wait()
#include <sys/types.h>  // pid_t

int main() 
{
    int num, factorial, square;
    int fd1[2], fd2[2], fd3[2], fd4[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1 
            || pipe(fd3) == -1 || pipe(fd4) == -1) 
    {
        printf("\nError! in creating pipe\n");
        exit(1);
    }

    pid_t C1 = fork();

    if (C1 < 0) {
        printf("\nError! in creating child process\n");
        exit(1);
    } 
    else if (C1 == 0) 
    {
        // first child process C1- calculate factorial

        // close write end of pipe
        close(fd1[1]);

        // reading from pipe
        read(fd1[0], &num, sizeof(int));

        // closing read end of pipe
        close(fd1[0]);

        factorial = 1;
        for (int i = 1; i <= num; i++) {
            factorial *= i;
        }

        // close read end of pipe 
        close(fd3[0]);

        // writing to pipe
        write(fd3[1], &factorial, sizeof(int));

        // close write end of pipe
        close(fd3[1]);

        exit(0);
    } 
    else if(C1 > 0) {
        pid_t C2 = fork();

        if (C2 < 0) {
            printf("\nError! in creating child process\n");
            exit(1);
        } 
        else if (C2 == 0) 
        {
            // second child process - calculate square

            // closing write end of pipe
            close(fd2[1]);  

            // reading from pipe
            read(fd2[0], &num, sizeof(int));

            // closing read end of pipe
            close(fd2[0]);

            square = num * num;

            // close read end of pipe
            close(fd4[0]);

            // writing to pipe
            write(fd4[1], &square, sizeof(int));

            // close write end of pipe
            close(fd4[1]);

            exit(0);
        } 
        else if(C2 > 0) {
            // parent process - get input from user, and wait for children

            // closing read end of pipe
            close(fd1[0]);
            close(fd2[0]);
            close(fd3[1]);
            close(fd4[1]);

            printf("\nI am parent process ID = %d\n",getpid());
            printf("Enter a number: ");
            scanf("%d", &num);

            // writing to pipe
            write(fd1[1], &num, sizeof(int));
            write(fd2[1], &num, sizeof(int));

            // closing write end of pipe
            close(fd1[1]);
            close(fd2[1]);

            // waiting for children
            wait(NULL);
            wait(NULL);

            // reading from pipe
            read(fd3[0], &factorial, sizeof(int));
            read(fd4[0], &square, sizeof(int));

            // closing read end of pipe
            close(fd3[0]);
            close(fd4[0]);

            // printing output
            printf("The Factorial of %d (calculated by C1 ID = %d)is %d \n", num,C1, factorial );
            printf("Square of %d (calculated by C2 ID = %d) is %d\n", num, C2,square);
        }
    }

    return 0;
}
/*
    Resources:
     1) https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_pipes.htm
*/
