/*
    Muhammad Mahad 21L-6195 
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
    int send_array[num_of_elements_in_array];
    int recv_array[1]; // the sum of the array will be a single integer
    int i, sum = 0;

    // open the named pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);

    // read the integer array from the handler process
    read(fd, send_array, sizeof(int) * num_of_elements_in_array);

    // close the read end of the named pipe
    close(fd);

    // calculate the sum of the array
    for (i = 0; i < num_of_elements_in_array; i++) {
        sum += send_array[i];
    }

    // open the named pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);

    // send the sum of the array to the handler process
    write(fd, &sum, sizeof(int));

    // close the write end of the named pipe
    close(fd);

    return 0;
}
