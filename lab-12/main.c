#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int lap_time, lap_count;

void my_signal_handler(int sig_num)
{
    if(sig_num == SIGCHLD)
    {
        printf("\nReceived SIGCHLD\n");
        printf("Total Time In Seconds : %d \n", lap_time * lap_count);
    }
    exit(0);
}


int main()
{
    signal(SIGCHLD, my_signal_handler);

    printf("Enter number of laps : ");
    scanf("%d", &lap_count);

    printf("Enter lap time : ");
    scanf("%d", &lap_time);

    

    __pid_t pid = fork();
    if (pid < 0){
        printf("\nFork Failed\n");
    }
    if(pid == 0)
    {
        // child process
        sleep(lap_time);
        
        for(int i = 0;i < lap_count ; i++){
            printf("\nLap %d Completed",i+1);
            sleep(lap_time);
        }

        exit(0);
    }
    else if(pid > 0)
    {
        wait(NULL);
        sleep(1);
    }
    return 0;
}