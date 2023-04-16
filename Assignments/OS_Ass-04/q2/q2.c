/*  21L-6195 Muhammad Mahad
 Thread_4 processes are involved in printing files characters (pictured below). Using semaphore(s),
order the execution of these processes such that t_A 10 characters are printed from each file 1
and 2. All Thread_4 processes are spawned by the parent process at the same time. However, the
execution of process D waits for the execution of process C. Whereas the execution of process C
waits for the execution of process A and B. Also, remember that process A and B can both write
on the same Buffer-1. Therefore, data must NOT be overwritten on Buffer-1 and synchronization
must be ensured on Buffer-1 between process A and B. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

sem_t t_A, second, third,printing;

char buff1[20];
char buff2[20];
int limit = 10;

void *Thread_1(void *args){
    sem_wait(&t_A);

    sem_wait(&printing);
    printf("\n We are in A thread [%ld]\n", pthread_self());
    sem_post(&printing);

    char c;
    FILE *f1 = fopen("A.txt", "r");
    int s = 0;
    while (s <= 10 - 1){
        c = fgetc(f1);
        buff1[s] = c;
        s++;
    }

    sem_post(&t_A);
    sem_post(&third);

    pthread_exit(NULL);
}
void *Thread_2(void *args){
    sem_wait(&t_A);

    sem_wait(&printing);
    printf("\n We are in B thread [%ld]\n", pthread_self());
    sem_post(&printing);

    char c;
    FILE *f2 = fopen("B.txt", "r");
    int s = 10;
    while (s <= 20 - 1){
        c = fgetc(f2);
        buff1[s] = c;
        s++;
    }

    sem_post(&t_A);
    sem_post(&second);
    pthread_exit(NULL);
}

void *Thread_3(void *args){
    sem_wait(&second);

    sem_wait(&printing);
    printf("\n We are in C thread [%ld]\n", pthread_self());
    sem_post(&printing);

    strcpy(buff2, buff1);
    sem_post(&third);
    pthread_exit(NULL);
}

void *Thread_4(void *args){
    sem_wait(&third);

    sem_wait(&printing);
    printf("\n We are in D thread [%ld]\n\nPrinting on Screen : \n", pthread_self());
    sem_post(&printing);

    puts(buff2);
    sem_post(&third);
    pthread_exit(NULL);
}

int main()
{
    pthread_t ids[4];
    sem_init(&t_A, 0, 1);
    sem_init(&second, 0, 0);
    sem_init(&third, 0, 1);
    sem_init(&printing, 0, 1);

    sem_wait(&printing);
    printf("\n We are in main thread [%ld]\n", pthread_self());
    sem_post(&printing);

    sem_wait(&third);
    pthread_create(&ids[0], NULL, Thread_1, NULL);
    sem_wait(&third);

    pthread_create(&ids[1], NULL, Thread_2, NULL);
    pthread_create(&ids[2], NULL, Thread_3, NULL);
    pthread_create(&ids[3], NULL, Thread_4, NULL);
    pthread_join(ids[3], NULL);

     sem_wait(&printing);
    printf("\n Exiting from main thread [%ld]\n", pthread_self());
    sem_post(&printing);
    return 0;
}
