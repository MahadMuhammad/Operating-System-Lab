/*
    Muhammad Mahad 21L-6195
*/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
  int res;
  res = mkfifo("fifo1", 0777);
  printf("named pipe created");
  return 0;
}
