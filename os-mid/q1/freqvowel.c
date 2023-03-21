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
    // printf("%s", buff);

    int fa, fe, fi, fo ,fu;
    fa = fe = fi = fo = fu = 0;

    for(int i = 0; buff[i] != '\0'; i++){
        if(buff[i] == 'a' || buff[i] == 'A'){
            fa++;
        }
        else if(buff[i] == 'e' || buff[i] == 'E'){
            fe++;
        }
        else if(buff[i] == 'i' || buff[i] == 'I'){
            fi++;
        }
        else if(buff[i] == 'o' || buff[i] == 'O'){
            fo++;
        }
        else if(buff[i] == 'u' || buff[i] == 'U'){
            fu++;
        }
    }

    printf("\nFrequeny of each vowel:");
    printf("\na:%d", fa);
    printf("\ne:%d", fe);
    printf("\ni:%d", fi);
    printf("\no:%d", fo);
    printf("\nu:%d\n", fu);


    char *argv[]={'\0'};
    execvp("./findsize.out",argv);
    printf("\nThis never run\n");

    exit(0);
}