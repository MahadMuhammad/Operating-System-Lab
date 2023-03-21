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
    char buff[100];
    FILE *fp = fopen("data.txt","r");
    fgets(buff,sizeof(buff),fp);
    // printf("%s", buff);

    // reversing the string
    int i = 0;
    int j = strlen(buff) - 1;

    while(i < j){
        char temp = buff[i];
        buff[i] = buff[j];
        buff[j] = temp;
        i++;
        j--;
    }

    printf("\nReversed Message:\n%s\n",buff);
    

    return 0;
}