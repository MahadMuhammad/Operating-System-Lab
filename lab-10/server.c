/*
- Create 2 processes, client and server
- A client process read data from a file named “number.txt” (passed as a command-line
argument) and sends the data to a server process (unrelated process) via shared
memory.
- The server process reads the data from the shared memory and display the sum and
average of the integers.
Note 1: Use open, read, and write system calls for file handling.
Note 2: Use strncpy for writing data to shared memory.
Sample Data for File:
12886
Output should be:
Sum = 25
Average = 5 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>

int main(int argc,char* argv[]);


int main(int argc,char* argv[])
{
    key_t key = ftok("number.txt",65);
    int shmid =  shmget(key,1024,0666|IPC_CREAT);
    // taking two numbers from file
    FILE *fp;
    fp = fopen("number.txt","r");
    int num1;//,num2;
    fscanf(fp,"%d",&num1);
    //fscanf(fp,"%d",&num2);
    fclose(fp);
    // writing to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);
    sprintf(str,"%d",num1);             
    str += sizeof(num1);
    // sprintf(str,"%d",num2);
    // str += sizeof(num2);
    shmdt(str);
    // successfull writing to shared memory

    return 0;
}

