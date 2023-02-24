/*
    Debug and compile the following piece of codes by including appropriate header files and write
    the output.

    Part 1:
*/
#include <stdio.h>      // for printf()
#include <unistd.h>     // for pipe()
#include <sys/types.h>      // for fork()
#include <sys/wait.h>       // for wait()
#include <string.h>     // for strlen() and strcpy() 
#include <stdlib.h>     // for exit()


char *mesag= "This is a message ";
int main()
{
    char buf[1024];
    int fd[2];
    pipe(fd);
    if(fork()!=0)
    {/* I am parent */
        write(fd[1], mesag, strlen(mesag) + 1);     // fd[1] is the write end of the pipe
    }
    else {/* child */
        read(fd[0],buf,1024);                   // fd[0] is the read end of the pipe
        printf("Got this from MaMa!!!\n%s\n", buf);
    }
return 0;
}