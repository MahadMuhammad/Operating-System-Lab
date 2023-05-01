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

// reading from shared memory and displaying sum and average

int main(int argc,char* argv[])
{
    key_t key = ftok("number.txt",65);
    int shmid =  shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    int num1;//,num2;
    sscanf(str,"%d",&num1);
    str += sizeof(num1);
    //sscanf(str,"%d",&num2);
    // int sum = num1 + num2;
    // float avg = (float)sum/2;

    // finding sum and average of digits
    int sum = 0;
    int count = 0;
    while(num1>0)
    {
        sum += num1%10;
        num1 /= 10;
        count++;
    }
    float avg = (float)sum/count;
    // displaying sum and average
    printf("Sum = %d\n",sum);
    printf("Average = %f\n",avg);
    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}