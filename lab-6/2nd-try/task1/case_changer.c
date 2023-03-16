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

    int res, n;
    char str[8];
    res = open("fifo1", O_RDONLY);
    n = read(res, str, 8);
    // printf("Reader process case_changer.c having PID %d started \n ", getpid());
    // printf("Data received by receiver %d is %s \n", getpid(), str);

    for (int i = 0; i < strlen(str); i++)
    {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = str[i] - 32;
            }
            else if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] = str[i] + 32;
            }
    }
    // sleep(6);
    res = open("fifo1", O_WRONLY);
    write(res, str,strlen(str)+1);
    // printf("Sender process case_changer.c having PID %d sent the data \n", getpid());
    // printf("\nThe output is :");
    // printf("%s ",str);
    // printf("\n\n");
    // sleep(6);
    return 0;
}