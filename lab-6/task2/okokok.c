/*
    Muhammad Mahad 21L-6195 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{
    int send_arr[5];
    // int send_arr[] = {1,5,7,2,15};

   

    

        // input in 5 size array
    int size = sizeof(int) * 5;
    int res, n;
    char str[100];
    res = open("fifo1", O_RDONLY);
    n = read(res,send_arr,sizeof(int) * 5);
    // printf("Reader process case_changer.c having PID %d started \n ", getpid());
    // printf("Data received by receiver %d is %s \n", getpid(), str);

    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
            sum += send_arr[i];
    }
    // sleep(6);
    res = open("fifo1", O_WRONLY);
    write(res, &sum,sizeof(int));
    printf("Sender process case_changer.c having PID %d sent the data \n", getpid());
    // printf("\nThe output is :");
    // printf("%d ",sum);
    // printf("\n\n");
    // sleep(6);
    return 0;
}