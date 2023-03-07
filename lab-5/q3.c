/*
    21L-6195 Muhammad Mahad

    Design a file-copying program named FileCopy using ordinary pipes. This program will be passed two
parameters: the first is the name of the file to be copied, and the second is the name of the copied file.
The program will then create an ordinary pipe and write the contents of the file to be copied to the
pipe. The child process will read this file from the pipe and write it to the destination file. For example,
if we invoke the program as follows:
 gcc FileCopy.c –o FileCopy
 FileCopy input.txt output.txt
The file input.txt will be written to the pipe. The child process will read the contents of this file and
write it to the destination file copy.txt.Help:
You will have to send the size of the read content through pipe to the parent before sending the actual content.
To get the size of string use strlen(co
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    // error argumentas
    if(argc < 3){
        printf("\nError! in arguments\n");
        exit(-1);
    }
    // creating a pipe
    int fd[2];

    if (pipe(fd) == -1 ) 
    {
        printf("\nError! in creating pipe\n");
        exit(-1);
    }

    pid_t f1 = fork();
    
    // creating a child to convert upper to lower and lower to upper
    if( f1 < 0){
        printf("\nError! in creating child\n");
        exit(-2);
    }
    if (f1 == 0)
    {
        // closing the read end of the pipe
        close(fd[0]);

        // opening the file to be copied
        FILE *fp = fopen(argv[1],"r");

        // checking if file is empty
        if(fp == NULL)
        {
            printf("\nError! in opening file\n");
            exit(-3);
        }

        // creating a string to store the content of the file
        char str[100];

        // reading the file
        fscanf(fp,"%[^\n]s",str);

        // closing the file
        fclose(fp);



        // sending the size of the string
        int size = strlen(str);
        write(fd[1],&size,sizeof(int));

        // sending the string
        write(fd[1],str,strlen(str));

        // closing the write end of the pipe
        close(fd[1]);
    }
    else
    {
        // parent process

        // closing the write end of the pipe
        close(fd[1]);

        // creating a string to store the content of the file
        char str[100];

        // reading the size of the string
        int size = 0;
        read(fd[0],&size,sizeof(int));
        
        // reading the string
        read(fd[0],str,size);

        // printing the string
        printf("\nDone :) ");


        // opening the file to be copied
        FILE *fp = fopen(argv[2],"w");

        // checking if file is empty
        if(fp == NULL)
        {
            printf("\nError! in opening file\n");
            exit(-3);
        }

        // writing the string to the file
        fprintf(fp,"%s",str);

        // closing the file
        fclose(fp);

        // closing the read end of the pipe
        printf("\nHave a good day :)\n");
        close(fd[0]);
    }

    return 0;

}
