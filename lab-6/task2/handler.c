/*
    Muhammad Mahad 21L-6195 

    Design a program (handler.c) which communicates using named pipes. handler sends a string message
to a second process (case_changer.c), and the second process reverses the case of each character in
the message and sends it back to the handler, that will print it on the screen.
For example, if the first process sends the message Hi There, the second process will return hi tHERE.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PIPE_NAME "/tmp/myfifo"

int main()
{
    int fd;
    int num_of_elements_in_array = 5;
    int send_array[] = {1, 2, 3, 4, 5};
    int recv_array[1]; // the sum of the array will be a single integer

    // create the named pipe
    mkfifo(PIPE_NAME, 0666);

    // open the named pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);

    // send the integer array to the calculator process
    int size = sizeof(int) * num_of_elements_in_array;
    write(fd, send_array, size);

    // close the write end of the named pipe
    close(fd);

    // wait for the calculator process to finish processing the array
    sleep(1);

    // open the named pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);

    // read the sum of the array from the calculator process
    read(fd, recv_array, sizeof(int));

    // display the result on screen
    printf("The sum of the array is: %d\n", recv_array[0]);

    // close the read end of the named pipe
    close(fd);

    // remove the named pipe
    unlink(PIPE_NAME);

    return 0;
}
