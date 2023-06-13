#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char c;
    char message[100];
    int i, j, size;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    i = 0;
    while ((c = fgetc(fp)) != EOF) {
        message[i] = c;
        i++;
    }
    message[i] = '\0';
    size = strlen(message);

    printf("Original message: %s\n", message);

    for (i = 0, j = size - 1; i < j; i++, j--) {
        char temp = message[i];
        message[i] = message[j];
        message[j] = temp;
    }

    printf("Reversed message: %s\n", message);

    fclose(fp);

    return 0;
}
