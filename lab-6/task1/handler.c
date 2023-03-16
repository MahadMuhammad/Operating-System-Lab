/*
    Muhammad Mahad 21L-6195 

    Design a program (handler.c) which communicates using named pipes. handler sends a string message
to a second process (case_changer.c), and the second process reverses the case of each character in
the message and sends it back to the handler, that will print it on the screen.
For example, if the first process sends the message Hi There, the second process will return hi tHERE.

*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char* argv [])
{
    // inputing string and storing it in a dynamic array
    printf("\n [PID = %d] Enter a string: ", getpid());
    char *str = (char *)malloc(100*sizeof(char));
    // with spaces
    scanf("%[^\n]%*c", str);

    

    int res;
    // send the string to the second proces with myfifo, opening fifo
    res = mkfifo("myfifo", 0777);
    /*
        O_CREAT: If the file does not exist, it will be created.
        O_EXCL: If O_CREAT and O_EXCL are set, open() will fail if the file exists.
        O_WRONLY: Open for writing only.

        0777: The file permission bits are set to this value.
    */
   
    //writing to pipe
    write(res, str, strlen(str)+1);
    close(1);

    // reading from pipe
    char *str2 = (char *)malloc(100*sizeof(char));
    read(0, str2, 100);
    close(0);

    sleep(1);

    // printing the output
    printf("\nOutput string is from process[%d]: %s",  getpid() , str2);
    printf("\n");
    return 0;
}
