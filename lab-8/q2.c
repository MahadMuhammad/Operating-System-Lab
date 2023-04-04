/*  Muhammad Mahad 21L-6195
Write a program that performs the task of the below shell command. cat input.txt > output.txt
“cat” command prints all the contents of a file onto “stdout” i.e. monitor.
“>” is used to redirect output when you are using shell/terminal.
Now you have to redirect output of “cat” command into a file called “output.txt”. Write any data of
your liking into input.txt file.
*/
#include <stdio.h>  // for printf
#include <fcntl.h>  // for open
#include <unistd.h> // for read, write, close
#include <stdlib.h> // for exit
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd0 = open(argv[1], O_RDONLY);
    if (fd0 == -1)
        printf("\nError opening file %s\n", argv[1]);
    
    int fd1 = open(argv[2], O_WRONLY | O_CREAT, 0777);
    if (fd1 == -1)
        printf("\nError opening file %s\n", argv[2]);
    dup2(fd0, 0);
    dup2(fd1, 1);
    char data[50] = {0};
    int status = read(0, data, 50);
    pid_t pid = fork();
    if (pid == 0)
    {
        //! CHILD
        char *arguments[] = {"cat",argv[1], NULL};
        execvp("cat", arguments);   
        printf("\nError in execvp\n");
        exit(1);
    }
    else
        wait(NULL);
    close(fd0);
    close(fd1);
    return 0;
}

