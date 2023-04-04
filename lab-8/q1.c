/*  Muhammad Mahad 21L-6195
Write a program that reads text from a file input.txt (name passed through command line arguments)
rather than a keyboard i.e. stdin.
Use open() and read() system calls.
Write this data to a new file output.txt rather than console, using printf(). Like this:•
This whole process is to be done by Dup2 system call.
(Hint: Replace stdin (0) value with input file’s file descriptor and stdout (1) value with output file’s file
descriptor)
*/
#include <stdio.h>  // for printf
#include <fcntl.h>  // for open
#include <unistd.h> // for read, write, close
#include <stdlib.h> // for exit

int main(int argc, char *argv[])
{
    int fd1,status;
    char data[100];
    if (argc != 3){
        printf("\nError Usage: %s <input files> <output file>\n", argv[0]);
    }

    fd1 = open(argv[1], O_RDONLY | O_CREAT, 0777);
    if(fd1 == -1)
        printf("\nError opening file %s]n", argv[1]);

    if((status = read(fd1, data, sizeof(data))) == -1)
        printf("\nError reading file %s]n", argv[1]);

    dup2(fd1, STDIN_FILENO);
    close(fd1);

    fd1 = open(argv[2], O_WRONLY | O_CREAT, 0777);
    if(fd1 == -1)
        printf("\nError opening file %s\n", argv[2]);
    
    status = dup2(fd1, STDOUT_FILENO);
    if(status == -1)
        printf("\nError in dup2 for file %s\n", argv[2]);

    // printf("\nThis is not printed on console\nReading from file %s and writing to file %s\n", argv[1], argv[2]);


    printf("%s", data);
    close(fd1);


    return 0;
}