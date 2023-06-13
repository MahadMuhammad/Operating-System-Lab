#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    int vowels[5] = {0}; // a, e, i, o, u
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha(ch)) {
            ch = tolower(ch);
            if (ch == 'a') {
                vowels[0]++;
            } else if (ch == 'e') {
                vowels[1]++;
            } else if (ch == 'i') {
                vowels[2]++;
            } else if (ch == 'o') {
                vowels[3]++;
            } else if (ch == 'u') {
                vowels[4]++;
            }
        }
    }

    fclose(fp);

    printf("Frequency of each vowel:\n");
    printf("a: %d\n", vowels[0]);
    printf("e: %d\n", vowels[1]);
    printf("i: %d\n", vowels[2]);
    printf("o: %d\n", vowels[3]);
    printf("u: %d\n", vowels[4]);

     char *args[] = {"./findsize", "data.txt", NULL};
            execvp(args[0], args);
}


