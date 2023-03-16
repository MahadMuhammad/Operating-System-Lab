/*
    Muhammad Mahad 21L-6195 

Create 2 independent programs (sender.c and worker.c) that perform communication using named pipes.
One program will be the worker program that will wait for sender to send some data
via a named pipe. The data sent is as follows:
Operator operand1 operand2
The operands can be +, -, *, /. The worker will then apply the operator on the
operands and return the result to sender via named pipe. The sender will then print
the result on the screen
For example, if the following is sent:
+ 4 10
Then the worker will calculate 4+10 and return 14 to sender via the pipe which will
then print it.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>

int main()
{
    int res;

    // read from fifo1
    int fd = open("fifo1", O_RDONLY);
    char op[100];
    read(fd, op, sizeof(op) );

    int size = strlen(op);

    char operator = strtok(op , ' ')[0];

    // convert string to int
    int operand1 = atoi(strtok(NULL, ' '));
    int operand2 = atoi(strtok(NULL, ' '));

    int result;
    switch (op[0])
    {
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
        break;
    }

    printf("\nResult is: %d\n", result);
    // write to fifo2
    fd = open("fifo1", O_WRONLY);
    write(fd, &result, sizeof(result));
    close(fd);
    
    return 0;
}