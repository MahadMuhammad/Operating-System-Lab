#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main()
{
    char *ALAN_TURING = "A computer would deserve to be called intelligent if it could deceive a human into believing that it was human";

    printf("\n%s\nFrequency are:\n", ALAN_TURING);
    // sending this message to receiver using story_pipe
     int writefd = open("story_pipe", O_WRONLY);

    if(writefd == -1){
        printf("\nError in opening pipe");
        exit(EXIT_FAILURE);
    }

    write(writefd, ALAN_TURING, strlen(ALAN_TURING));



    return 0;
}
