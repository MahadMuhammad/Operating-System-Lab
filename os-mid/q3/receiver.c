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
    // recieving from sender using story_pipe
    int readfd = open("story_pipe", O_RDONLY);

    if(readfd == -1){
        printf("\nError in opening pipe");
        exit(EXIT_FAILURE);
    }

    // stopwords
    char *stopwords[] = {"a", "an", "the","of", "to", "in","and"};

    // counting freq of each stopwords
    int freq[7] = {0,0,0,0,0,0,0};

    // reading from pipe
    char buffer[100];
    int n = read(readfd, buffer, 100);
    buffer[n] = '\0';

    // tokenizing
    char *token = strtok(buffer, " ");
    while(token != NULL){
        for(int i=0; i<7; i++){
            if(strcmp(token, stopwords[i]) == 0){
                freq[i]++;
            }
        }
        token = strtok(NULL, " ");
    }

    // printing freq
    for(int i=0; i<7; i++){
        printf("%s: %d times \n", stopwords[i], freq[i]);
    }





    return 0;
}