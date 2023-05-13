#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
sem_t semo, semo1, semo2, semo3;
struct numbs
{
    int X;
    int Y;
    int Z;
    int W;
};
void *first(void *one)
{
    struct numbs *mine = (struct numbs *)one;
    sem_wait(&semo);
    int temp1;
    temp1 = mine->Z;
    mine->X = temp1 + 2;
    sem_post(&semo1);

    sem_wait(&semo2);
    mine->Y = mine->Z * 5;
    sem_post(&semo3);

    int r = mine->X + mine->Y;
    printf(" First result is %d ", r);
}
void *second(void *two)
{
    struct numbs *mine = (struct numbs *)two;
    sem_wait(&semo1);
    int temp1;
    temp1 = mine->X;
    mine->Z = temp1 * 2;
    sem_post(&semo2);

    sem_wait(&semo3);
    mine->W = mine->Y + 5;

    int r = mine->Z + mine->W;
    printf(" SEcond result is %d ", r);
}

int main(int argc, char *argv[])
{
    sem_init(&semo, 0, 1);
    sem_init(&semo1, 0, 0);
    sem_init(&semo2, 0, 0);
    sem_init(&semo3, 0, 0);

    int arr[4];
    for (int i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }
    for (int i = 0; i < argc - 1; i++)
    {
        printf(" %d", arr[i]);
    }
    struct numbs mine;
    mine.X = arr[0];
    mine.Y = arr[1];
    mine.Z = arr[2];
    mine.W = arr[3];

    pthread_t id[2];
    printf("\n");
    pthread_create(&id[0], NULL, first, &mine);
    pthread_create(&id[1], NULL, second, &mine);
    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
}
