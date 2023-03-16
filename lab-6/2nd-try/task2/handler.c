/*
    Muhammad Mahad 21L-6195 

    Design a program (handler.c) which communicates using named pipes. handler sends a string message
to a second process (case_changer.c), and the second process reverses the case of each character in
the message and sends it back to the handler, that will print it on the screen.
For example, if the first process sends the message Hi There, the second process will return hi tHERE.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
    int res;
    res = mkfifo("fifo1", 0777);
    // input array
    int send_arr[] = {1,5,7,2,15};

        // input in 5 size array
    int size = sizeof(int) * 5;

    int n;
    res = open("fifo1", O_WRONLY);
    write(res, send_arr,size);
    // printf("Sender process handler.c having PID %d sent the data \n", getpid());



    
    int sum = 0;
    res = open("fifo1", O_RDONLY);
    n = read(res,&sum, sizeof(int));
    // printf("Reader process case_changer.c having PID %d started \n ", getpid());
    // printf("Data received by receiver %d is %s \n", getpid(), str);

    printf("\nThe output is :");
    printf("%d ",sum);
    printf("\n\n");

    // sleep(5);
    return 0;
}