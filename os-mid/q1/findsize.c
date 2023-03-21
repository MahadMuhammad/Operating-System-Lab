#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>


int main()
{
    char buff[100];
    FILE *fp = fopen("data.txt","r");
    fgets(buff,sizeof(buff),fp);
    printf("%s", buff);

    int i = 0;
    for(; buff[i] != '\0'; ){
        i++;
    }
    printf("\nThe size of the message is : %d\n",i);

    char *argv[]={'\0'};
    execvp("./reverse.out",argv);
    printf("\nThis never run\n");
    exit(0);
}