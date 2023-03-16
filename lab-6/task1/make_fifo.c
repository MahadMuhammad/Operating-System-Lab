/*
  Muhammad Mahad 21L-6195

  Making a named pipe (FIFO) in Linux
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  // creating a named pipe
  if (mkfifo("myfifo", 0777)){
    perror("mkfifo");
    printf("\nError in creating a named pipe\n");
    exit(EXIT_FAILURE);
  }

  printf("\nNamed pipe created successfully\n");

  return 0;
}