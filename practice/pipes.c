// Implementing the pipe system call

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;
    char buf[30];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid > 0) { // parent
        close(fd[0]);
        write(fd[1], "hello world ", 12);
    } else { // child
        close(fd[1]);
        read(fd[0], buf, 12);
        printf("read \"%s\" from the pipe in child process %d", buf, getpid()); 
    }

    return 0;
}