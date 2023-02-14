#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main()
{
  pid_t p, cpid;
  printf("main id %d\n",getpid());
  printf("before fork\n");
  p=fork();
  if(p==0)
  {
    printf("I am child having id %d\n",getpid());
    printf("My parent's id is %d\n",getppid());
    exit(0);
  }
  else if(p>0)
  {
      cpid = wait(NULL);
    printf("My child's id is %d\n",p);
    printf("I am parent having id %d\n",getpid());
  }
  else
  {
      printf("ERROR");
  }
  printf("Your quiz is expected in next class\n");
}