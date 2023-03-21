#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    int status = 0;

    if(pid < 0){
        printf("\nError in creating child\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // writing to file data.txt
        FILE *fp = fopen("data.txt","w");
        fprintf(fp,"This is a test message.");
        exit(0);
    }
    else if (pid > 0)
    {
        // parent process
        wait(&status);

        char *argv[]={'\0'};
        execvp("./freqvowel.out",argv);
        printf("\nThis never run\n");
    }
    
    return 0;
}
