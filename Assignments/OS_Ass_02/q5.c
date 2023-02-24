/*
    Muhammad Mahad 21L-6195

    (a) Write another program to issue the fork system call. Complete the following code for the
        provided requirements.
    (b) Complete the two cases above. One should execute only in child process and should print "In
        child" and the child’s process ID. The second should run only if we are in parent and print both
        the parent’s and the child’s PID.
*/

/* fork: create a new process */
#include <stdlib.h> // needed for exit()
#include <stdio.h> // needed for printf()
#include <unistd.h> // needed for fork()

int main(int argc, char **argv)
{
    int pid;    // process id

    switch (pid = fork())
    {
        // two cases here to check if we are in the child or parent process
        case -1:   // error
            perror("fork");     //print error messsage
            exit(1);            // no need to break here
        case 0:    // pid == 0 , child process
            printf("\nI am Child Process: my pid = %d,",getpid());
            printf("\nMy parent's PID = %d :",getppid());
            exit(0);
        default:   // pid > 0, parent process
            printf("\nI am Parent Process and my pid = %d ",getpid());
            printf("\nMy child Process id = %d ",pid);
            break;
    }
    exit(0);
}