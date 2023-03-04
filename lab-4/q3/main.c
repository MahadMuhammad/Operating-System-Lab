/*
    Muhammad Mahad 21L-6195

    Task 3: execv ( )
• Create a program that makes a child and that child replaces itself via execv with another
program called Fibonacci.• This Fibonacci program takes a command line argument n.
• You have to print first n numbers from the Fibonacci series in that new program.
*/
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // First checking if command line argument is passed or not
    if(argc != 2){
        printf("\nError in command line argument\n");
        return 1;
    }

    // First making a child

    pid_t f1;

    f1 = fork();
    if(f1 < 0){
        printf("\nError in creating child\n");
        exit(EXIT_FAILURE);
    }
    else if(f1 == 0)
    {
        // We are in child process
        // Now we have to replace child with Fibonacci program
        // So, we use execv

        // First, we have to create an array of arguments
        // taking command line argument n
        char *args[] = {"./fibonacci.out", argv[1], NULL};

        execv(args[0],args);

        // If execv fails, it returns -1
        printf("\nError in execv\n");

        exit(EXIT_FAILURE);
    }
    else{
        wait(NULL);
        printf("\nChild process terminated\n");
        printf("\nHave a great day :) \n");
    }
    return 0;
}