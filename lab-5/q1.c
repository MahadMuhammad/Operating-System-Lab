/*
    21L-6195 Muhammad Mahad

    Design a program using ordinary pipes in which one process (parent) sends a string message to a second
process (child), and the second process reverses the case of each character in the message and prints
it on the screen.
For example, if the first process sends the message Hi There, the second process will print hi tHERE.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    // creating a string
    char str[100];
    printf("\nEnter a string : ");
    scanf("%[^\n]s",str);

    //printing the string
    printf("\nOrignal String is : ");
    printf("%s ",str);
    printf("\n");

    int fd1[2];

    if (pipe(fd1) == -1 ) 
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
        close(fd1[0]);

        // converting the string
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = str[i] - 32;
            }
            else if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] = str[i] + 32;
            }
        }

        // writing the string to the pipe
        write(fd1[1],str,strlen(str)+1);
        close(fd1[1]);

        printf("\nChild Process ID : %d\n",getpid());
        printf("\nChild Process Parent ID : %d\n",getppid());
    }
    else
    {
        // closing the write end of the pipe
        close(fd1[1]);

        // waiting for the child to finish
        wait(NULL);

        // reading the string from the pipe
        read(fd1[0],str,strlen(str)+1);
        // printing the string
        printf("\nModified String is : ");
        printf("%s ",str);
        close(fd1[0]);
    }

    // clear the buffer
    fflush(stdin);
    printf("\n");
    return 0;
}
