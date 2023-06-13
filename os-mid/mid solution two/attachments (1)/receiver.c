#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIPE_NAME "fifo1"

#define STOP_WORDS_COUNT 7

char stop_words[STOP_WORDS_COUNT][10] = {"a",  "an", "the", "of",
                                         "to", "in", "and"};

int main() {
  int fd;
  char buffer[112];
  int stop_words_count[STOP_WORDS_COUNT] = {0};
  char *word, *ptr;

  // Opening the named pipe for reading
  fd = open(PIPE_NAME, O_RDONLY);

  // Reading the story from the named pipe
  read(fd, buffer, sizeof(buffer));
  
  for (int i=0; i<sizeof(buffer);i++)
  {
  printf("%c",buffer[i]);
  }
  
  // Counting the frequencies of stop words in the story
  word = strtok_r(buffer, " ,.-", &ptr);
  while (word != NULL) {
    for (int i = 0; i < STOP_WORDS_COUNT; i++) {
      if (strcmp(word, stop_words[i]) == 0) {
        stop_words_count[i]++;
        break;
      }
    }
    word = strtok_r(NULL, " ,.-", &ptr);
  }

  // Displaying the frequencies of stop words
  printf("Stop Words Frequencies:\n");
  for (int i = 0; i < STOP_WORDS_COUNT; i++) {
    printf("%s: %d\n", stop_words[i], stop_words_count[i]);
  }

  // Closing the named pipe
  close(fd);
  unlink(PIPE_NAME);

  return 0;
}
