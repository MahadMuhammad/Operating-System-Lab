#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        printf("Error: failed to create child process\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child process
        FILE *fp = fopen("data.txt", "w");
        if (fp == NULL) {
            printf("Error: failed to open file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "This is a test message.\n");
        fclose(fp);
        exit(EXIT_SUCCESS);
    } else {
        // parent process
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            char *args[] = {"./readfile", "data.txt", NULL};
            execvp(args[0], args);
            printf("Error: failed to execute command\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Error: child process failed\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
