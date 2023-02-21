/*
    Muhammad Mahad 21L-6195
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printArray(int arr[5][5])
{
    printf("This array is : \n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf(" %d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int arr[5][5];
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            arr[i][j] = rand() % 1000;
        }
    }
    printArray(arr);

    pid_t pid = fork();
    if (pid == 0)   // Child process
    {
        
        //printf("\nI am child process.\n");
        int freq[1000] = {0};
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                // printf("arr[%d][%d] = %d ", i, j, arr[i][j]);
                freq[arr[i][j]]++;
            }
        }
        for (i = 0; i < 1000; i++)
        {
            if (freq[i] != 0)
            {
                printf("Frequency of %d is %d times.\n", i, freq[i]);
            }        
            int freq[1000] = {0};
            for (i = 0; i < 5; i++)
            {
                for (j = 0; j < 5; j++)
                {
                    freq[arr[i][j]]++;
                }
            }
            for (i = 0; i < 1000; i++)
            {
                if (freq[i] != 0)
                {
                    printf("Frequency of %d is %d times.\n", i, freq[i]);
                }
            }
        }
        printf("\nI am Child process ID: %d and Parent process ID: %d\n", getpid(), getppid());
    }
    else if(pid>0)  // Parent process
    {
        wait(NULL);
        int upper,lower=0;
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                if(i<j)
                    upper += arr[i][j];
                else if(i>j)
                    lower += arr[i][j];
            }
        }
        printf("\n\nI am parent process\nUpper triangular sum is %d and lower triangular sum is %d.\n", upper, lower);
        printf("My ID is: %d and Child process ID: %d\n", getpid(), pid);
        wait(NULL);
    }
    return 0;
}