#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char c;
    int size = 0;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF) {
        size=size+1;
        
    }
    size=size-1;

    printf("The size of the message is: %d\n", size);

    fclose(fp);

     char *args[] = {"./reverse", "data.txt", NULL};
            execvp(args[0], args);
}
