/*
    Muhammad Mahad 21L-6195

    Develop a stopwatch with lap counter and total time calculator. The program will create two
    processes and they will start calculating time. One process will be used to calculate total time
    and the other will calculate lap time. The total time calculator process will keep on calculating
    time. In the lap time, calculator process when it reaches lap time limit, the process will display
    lap number and set its counter to zero and start calculating again. Take input of lap time and
    number of laps from the user and start the program. At the end, display total time from total time
    calculator process.
*/

#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // exit()
#include <unistd.h>     // fork(), pipe()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait()
#include <time.h>       // time()

int main()
{
    printf("\n    --- Welcome to Stopwatch ---\n ");

    int lapTime, lapCount;
    
    printf("\nEnter lap time: ");
    scanf("%d", &lapTime);

    printf("\nAlso, Enter lap count: ");
    scanf("%d", &lapCount);

    int fd[2];

    if(pipe(fd) == -1)
    {
        printf("\nError! in creating pipe\n");
        exit(1);
    }


    pid_t pid = fork();

    if (pid < 0)
    {
        printf("\nError! in creating fork\n");
        exit(1);
    }
    else if (pid > 0)   // parent process
    {
        // This will calculate total time
        wait(NULL);
        int total;

        // closing writing end of the pipe
        close(fd[1]);

        // reading total from child
        read(fd[0], &total, sizeof(int));

        // closing reading end
        close(fd[0]);

        //printf("\nTotal time: %d", total);
        sleep(1);
        exit(EXIT_SUCCESS);
        printf("\n");
    }
    else if (pid == 0)
    {
        // child process
        int lap = 0;
        int lapTimeCounter = 0;
        int total = 0;
        while (lap < lapCount)
        {
            lapTimeCounter++;
            total++;
            if (lapTimeCounter == lapTime)
            {
                lap++;
                printf("\nLap %d: %d", lap, lapTimeCounter);
                lapTimeCounter = 0;
            }
            sleep(1);
            printf("\n TOTAL TIME: %d", total);
        }

        // closing reading end of the pipe
        close(fd[0]);

        // writing total to parent
        write(fd[1], &total, sizeof(int));

        // closing writing end
        close(fd[1]);

        exit(EXIT_SUCCESS);
    }


    return 0;
}

