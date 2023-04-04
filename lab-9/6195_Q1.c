/*  Muhammad Mahad 21L-6195
Write a program that creates N number of threads using a loop.
Print thread ID and process ID in each thread worker.
Also, create a suitable MAKEFILE for the execution of this program.
*/
#include <stdio.h>      // printf
#include <pthread.h>    // pthread_create, pthread_exit
#include <unistd.h>     // sleep
#include <stdlib.h>     // exit
int COUNT=1;
void* thread_worker(void *arg){
    printf("\n[%d] Thread ID: %lu",COUNT,pthread_self());
    printf("\n   Process ID: %d",getpid());
    COUNT++;
    pthread_exit(NULL);
}

int main(int argc,char* argv[])
{
    int N;
    printf("\nEnter the number of threads: ");
    scanf("%d",&N);
    pthread_t thread[N];
    
    for(int i=0; i < N; i++){
        pthread_create(&thread[i], NULL, thread_worker, NULL);
        sleep(1);
    }
    printf("\n ------ MAIN ENDED ------ \n");
    return 0;
}
