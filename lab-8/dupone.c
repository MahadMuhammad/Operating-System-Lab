#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int fd1, fd2;
  fd1 = open("file.txt", O_RDONLY);
  fd2 = dup(fd1);
  close(fd1);
  // use fd2 to read from file.txt
  printf("\nThe value of fd1 is = %d", fd1);
  printf("\nThe value of fd2 is = %d\n", fd2);
  return 0;
}