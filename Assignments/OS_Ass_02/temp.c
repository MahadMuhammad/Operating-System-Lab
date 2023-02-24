#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int lap_time, num_laps, lap_counter = 1;
    time_t start_time, current_time, lap_start_time, lap_end_time, total_time = 0, lap_time_elapsed;

    printf("Enter lap time in seconds: ");
    scanf("%d", &lap_time);
    printf("Enter number of laps: ");
    scanf("%d", &num_laps);

    start_time = time(NULL);

    // Create a child process to calculate lap time
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        lap_start_time = time(NULL);

        while (lap_counter <= num_laps) {
            sleep(lap_time);
            lap_end_time = time(NULL);
            lap_time_elapsed = lap_end_time - lap_start_time;
            printf("Lap %d time: %ld seconds\n", lap_counter, lap_time_elapsed);
            lap_start_time = lap_end_time;
            lap_counter++;
        }
        exit(0);
    } else if (pid > 0) 
    {  // Parent process
        while (total_time = time(NULL) - start_time < lap_time * num_laps) {
            current_time = time(NULL);
            total_time = current_time - start_time;
            printf("Total time: %ld seconds\n", total_time);
            sleep(1);
        }
    } else {  // Error
        fprintf(stderr, "Error: fork() failed\n");
        exit(1);
    }

    return 0;
}
