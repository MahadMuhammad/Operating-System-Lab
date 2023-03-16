#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*
    case_changer.c), and the second process reverses the case of each character in
the message and sends it back to the handler, that will print it on the screen
*/

int main()
{
    // reading from pipe
    printf("\n[PID = %d] Processing string from handler.c", getpid());
    char *str = (char *)malloc(100*sizeof(char));
    read(0, str, 100);
    close(0);

    // changing the case of each character
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

    
    // writing to pipe
    write(1, str, strlen(str)+1);
    close(1);

    return 0;
}