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
    // creating pipe

    if(mkfifo("story_pipe",0777)){
        printf("\nError in creating pipe OR Pipe already exists");
        exit(EXIT_FAILURE);
    }
    return 0;
}