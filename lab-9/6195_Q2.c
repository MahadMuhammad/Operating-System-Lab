/*  Muhammad Mahad 21L-6195
Design a multi-threaded program that performs the summation of a integer in
a separate thread using the summation function.
For example, if N were 5, this summation function would represent the summation of
integers from 0 to 5, which is 15.
Also, create a suitable MAKEFILE for the execution of this program.
*/
#include <stdio.h>    // printf
#include <pthread.h>  // pthread_create, pthread_exit
#include <unistd.h>   // sleep
#include <stdlib.h>   // exit
#include <stdint.h>   // intptr_t

void *thread_summation(void *arg){
     printf("\nCalculation by Thread [%lu] \n",pthread_self());
    int N = *(int*)arg;
    int sum = 0;
    for(int i=0; i <= N; i++){
        sum += i;
    }
    // printf("\nSummation of %d is %d",N,sum);
    pthread_exit((void*)(intptr_t)sum);
}

int main(int argc,char* argv[])
{
    int N,sum;
    printf("\nEnter the number: ");
    scanf("%d",&N);
    pthread_t thread;
    pthread_create(&thread, NULL, thread_summation, &N);
    pthread_join(thread, (void**)&sum);
    printf("\nSummation of %d is %d",N,sum);
    printf("\n ------ MAIN ENDED ------ \n");
    return 0;
}
