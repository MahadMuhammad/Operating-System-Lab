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
    printf("named pipe created");

    int n;
    res = open("fifo1", O_WRONLY);
    write(res, "Hi There", 8);
    // printf("Sender process handler.c having PID %d sent the data \n", getpid());


    char str[100];
    // fflush(stdin);
    // sleep(5);
    res = open("fifo1", O_RDONLY);
    n = read(res, str, 8);
    // printf("Reader process case_changer.c having PID %d started \n ", getpid());
    // printf("Data received by receiver %d is %s \n", getpid(), str);

    printf("\nThe output is :");
    printf("%s ",str);
    printf("\n\n");
    return 0;
}