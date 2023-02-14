/*
•Write C program that asks the user for input between 1 to 10 via command
line arguments.
•Then it creates that many processes such that each process is a parent of
exactly one process, except one (last one).
•The last process is not the parent of any process.
•Each child process should print its own and parent’s ID.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
    // taking a number from user between 1 to 10
    int n=atoi(argv[1]);

    //create a dynamic array of size n
    pid_t *arr=(pid_t *)malloc(n*sizeof(pid_t));
    for(int i=0;i<n;i++)
    {
        arr[i]=fork();
        if(arr[i]>0)
        {
            printf("I am child process and my ID = %d and parent's ID = %d\n",getpid(),getppid()+i+random_number);
            wait(NULL);
            exit(0);
        }

    }


    // free the memory
    free(arr);
    return 0;
}
