#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE_NAME "fifo1"

int main() {
  int fd;
  char buffer[1024];

  // Creating a named pipe
  mkfifo(PIPE_NAME, 0666);

  // Opening the named pipe for writing
  fd = open(PIPE_NAME, O_WRONLY);

  // Sending the story to the other process
  strcpy(buffer, "A computer would deserve to be called intelligent if it "
                 "could deceive a human into believing that it was human");
  write(fd, buffer, strlen(buffer) + 1);

  // Closing the named pipe
  close(fd);
  unlink(PIPE_NAME);

  return 0;
}
