/*
  Muhammad Mahad 21L-6195

  Write a program that creates a child process using fork ().The child displays its ID and parent ID.
  The Parent displays its own ID and its child ID. The output should be of the form:
        I am parent my ID is=1234 and my Child ID is=4567
        I am Child my ID is=4567 and my Parent ID is=1234
*/

#include <stdio.h>  // for printf
#include <stdlib.h> // for exit
#include <unistd.h> // for fork
#include <sys/types.h>  // for pid_t

int main()
{
  pid_t c_pid;  // child process id

  c_pid = fork(); // create child process

  if (c_pid > 0) // I am Parent process
  {
    printf("\nI am parent my ID is=%d and my Child ID is=%d",getpid(),c_pid);
  }
  else if(c_pid == 0) // I am Child Process
  {
    printf("\nI am Child my ID is=%d and my Parent ID is=%d\n",getpid(),getppid());
  }
  else // fork failed
  {
    printf("\n ERROR! FORK FAILED\n");
    exit(1);
  }

  return 0;
}
