/*
    21L-6195 Muhammad Mahad

    Design a program using ordinary pipes in which one process send an integer array to its child and child
calculates its sum and send it back to the parent and parent displays the result.
This will require using two pipes, one for sending the original message from the first to the second
process, and the other for sending the modified message from the second process back to the first
process.
Help:
Use int size = sizeof(int) * num_of_elements_in_array;
Syntax:
write(fd[1], send_array, size);
read(fd[0], recv_array, size);
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    // creating two pipes
    int fd1[2],fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1){
        printf("\nError in creating pipes\n");
        exit(-1);
    }

    pid_t f1 = fork();

    // taking input array from parent and sending it to child
    if(f1 > 0)
    {
        //parent process

        // input array
        int send_arr[] = {1,5,7,2,15};

        // input in 5 size array
        int size = sizeof(int) * 5;

    //     for(int i = 0; i < 5; i++)
    //     {
    //         // input array
    //         scanf("%d",&send_arr[i]);
    //     }

        // closing the read end of the pipe
        close(fd1[0]);

        // sending the array to child
        write(fd1[1],send_arr,size);

        // closing the write end of the pipe
        close(fd1[1]);

        // waiting for child to send the sum
        wait(NULL);

        // closing the write end of the pipe
        close(fd2[1]);

        // receiving the sum from child
        int sum;
        read(fd2[0],&sum,sizeof(int));

        // closing the read end of the pipe
        close(fd2[0]);

        // printing the sum
        printf("\nSum recieved from child : %d ",sum);
        printf("\n");
    }
    else if (f1 == 0)
    {
        //child process

        // closing the write end of the pipe
        close(fd1[1]);

        // receiving the array from parent
        int recv_arr[5];
        read(fd1[0],recv_arr,sizeof(int) * 5);

        // closing the read end of the pipe
        close(fd1[0]);

        // calculating the sum
        int sum = 0;
        for(int i = 0; i < 5; i++)
        {
            sum += recv_arr[i];
        }

        // closing the read end of the pipe
        close(fd2[0]);

        // sending the sum to parent
        write(fd2[1],&sum,sizeof(int));

        // closing the write end of the pipe
        close(fd2[1]);

        exit(0);
    }
    if( f1 < 0){
        printf("\nError! in creating child\n");
        exit(-2);
    }
    return 0;
}