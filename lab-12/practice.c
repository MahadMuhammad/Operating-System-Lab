#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void mahad_signal_handler(int sig_num)
{
    if(sig_num  == SIGINT)
    {
        printf("\nI have handled exception successfully\n");
    }
    exit(0);
}

int main()
{
    if( signal(SIGINT, mahad_signal_handler) == SIG_ERR){
        printf("Couldn't catch signal\n");
    }
    while(1)
    {
        sleep(1);
    }
    return 0;
}