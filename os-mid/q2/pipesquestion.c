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
    
    if(mkfifo("myfifo1",0777)){ 
        printf("\nError in creating pipe OR Pipe already exists");
        exit(EXIT_FAILURE);
    }

    
    
    
    pid_t pid = fork();
    int status = 0,size=22;

    if(pid < 0){
        printf("\nError in creating child\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // writing message to pipe

        // writing message to pipe
        int fd = open("myfifo1", O_WRONLY);
        char *msg= "This is a test message.";

        write(fd, msg, strlen(msg) + 1);

        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        int fd = open("myfifo1", O_RDONLY);
        char msg[100];
        read(fd, msg, sizeof(msg));

        printf("\nMessage received from child: %s\n", msg);

        //counting words
        int count = 1;
        for (int i = 0; i < strlen(msg); i++)
        {
            if (msg[i] == ' ')
            {
                count++;
            }
        }

        printf("\nNumber of words in the message is: %d\n", count);

        


        // if(mkfifo("myfifo2",0777)){ 
        // printf("\nError in creating pipe OR Pipe already exists");
        // exit(EXIT_FAILURE);
        // }

        // //writing count to myfifo2
        // int fd2 = open("myfifo2", O_WRONLY);

        // write(fd2, &count, sizeof(count));

        // counting average length of words

        // typecasting to float to get decimal value

        int avg = strlen(msg) / count;

        printf("\nAverage length of words(in int) in the message is: %d\n",avg);




        

    }

    return 0;
}