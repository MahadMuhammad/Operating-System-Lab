/*  21L-6195 Muhammad Mahad
 Four processes are involved in printing files characters (pictured below). Using semaphore(s),
order the execution of these processes such that first 10 characters are printed from each file 1
and 2. All four processes are spawned by the parent process at the same time. However, the
execution of process D waits for the execution of process C. Whereas the execution of process C
waits for the execution of process A and B. Also, remember that process A and B can both write
on the same Buffer-1. Therefore, data must NOT be overwritten on Buffer-1 and synchronization
must be ensured on Buffer-1 between process A and B. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Global variables
int buffer1[10];
int buffer2[10];
int buffer3[10];
int buffer4[10];

// creating custom semaphore
sem_t semA, semB, semC, semD;

// atomic wait
void wait(sem_t *sem) {
    sem_wait(sem);
}

// atomic signal
void signal(sem_t *sem) {
    sem_post(sem);
}

// function to print buffer
void printBuffer(int buffer[]) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

// functions prototypes
void *A(void *arg);
void *B(void *arg);
void *C(void *arg);
void *D(void *arg);

int main()
{
    // creating threads
    pthread_t thread1, thread2, thread3, thread4;

    // initializing semaphores
    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    sem_init(&semD, 0, 0);

    // creating threads
    pthread_create(&thread1, NULL, &A, NULL);
    pthread_create(&thread2, NULL, &B, NULL);
    pthread_create(&thread3, NULL, &C, NULL);
    pthread_create(&thread4, NULL, &D, NULL);

    // joining threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    // destroying semaphores
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    sem_destroy(&semD);

    return 0;
}

// function A
void *A(void *arg) {
    // filling buffer 1
    for (int i = 0; i < 10; i++) {
        buffer1[i] = i;
    }
    // printing buffer 1
    printf("Buffer 1: ");
    printBuffer(buffer1);
    // signaling semaphore A
    signal(&semA);
    // signaling semaphore B
    signal(&semB);
    // waiting for semaphore C
    wait(&semC);
    // printing buffer 3
    printf("Buffer 3: ");
    printBuffer(buffer3);
    // signaling semaphore D
    signal(&semD);
}

// function B
void *B(void *arg) {
    // waiting for semaphore A
    wait(&semA);
    // filling buffer 2
    for (int i = 0; i < 10; i++) {
        buffer2[i] = i;
    }
    // printing buffer 2
    printf("Buffer 2: ");
    printBuffer(buffer2);
    // signaling semaphore C
    signal(&semC);
}

// function C
void *C(void *arg) {
    // waiting for semaphore B
    wait(&semB);
    // filling buffer 3
    for (int i = 0; i < 10; i++) {
        buffer3[i] = i;
    }
    // printing buffer 3
    printf("Buffer 3: ");
    printBuffer(buffer3);
    // signaling semaphore C
    signal(&semC);
}

// function D
void *D(void *arg) {
    // waiting for semaphore C
    wait(&semC);
    // filling buffer 4
    for (int i = 0; i < 10; i++) {
        buffer4[i] = i;
    }
    // printing buffer 4
    printf("Buffer 4: ");
    printBuffer(buffer4);
    // signaling semaphore D
    signal(&semD);
}