/*
    Debug and compile the following piece of codes by including appropriate header files and write
    the output.

    Part 2:
*/
#include <stdio.h>      // for printf()
#include <unistd.h>     // for pipe()
#include <sys/types.h>      // for fork()
#include <sys/wait.h>       // for wait()
#include <string.h>     // for strlen() and strcpy()
#include <stdlib.h>     // for exit()



char *who = "who";
int main()
{
    int pfds[2];        // pfds[0] is the read end of the pipe, pfds[1] is the write end of the pipe
    pipe(pfds);         // create the pipe
    if (!fork())        // child process
    {
        close(1);       // close the write end of the pipe
        dup(pfds[1]);           // duplicate the write end of the pipe to stdout
        close(pfds[0]);         // close the read end of the pipe
        execlp("who", who,"-a", NULL);     // execute the who command
    }
    else        // parent process
    {
        close(0);           // close the read end of the pipe
        dup(pfds[0]);       // duplicate the read end of the pipe to stdin
        close(pfds[1]);     // close the write end of the pipe
        execlp("wc", "wc", "-l", NULL);     // execute the wc command
    }
    return 0;
}