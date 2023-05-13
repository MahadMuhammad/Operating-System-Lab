#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;//,s2;    // s1 for T1 and s2 for T2

// thread 1
void *thread1(void *arg)
{
    int *num = (int *)arg;
    int x1,y1,sum1;
    sem_wait(&s1);
    x1 = num[0] + 2;
    y1 = num[2] * 5;
    sum1 = x1 + y1;
    printf("\nX = %d\n",sum1);
    sem_post(&s1);
    pthread_exit(NULL);
}

// thread 2
void *thread2(void *arg)
{
    int *num = (int *)arg;
    int z1,w1,s2;
    sem_wait(&s1);
    z1 = num[0] * 2;
    w1 = num[1] + 5;
    s2 = z1 + w1;
    printf("\nY = %d\n",s2);
    sem_post(&s1);
    pthread_exit(NULL);
}


int main(int argc,char const *argv[])
{
    int num[4] = {0};
    sem_init(&s1,0,1);      // 0 for thread and 0 for shared between threads
    // sem_init(&s2,0,0);      // 0 for thread and 0 for shared between threads

    // if (argc != 5)
    // {
    //     printf("\nInvalid number of arguments\n");
    //     exit(0);
    // }
    // for (int i = 1; i < argc; i++)
    // {
    //     num[i-1] = atoi(argv[i]);
    // }
    printf("\nEnter the value of X,Y,Z,W: ");
    for (int i = 0; i < 4; i++)
    {
        scanf("%d",&num[i]);
    }
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,(void *)num);
    pthread_create(&t2,NULL,thread2,(void *)num);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&s1);
    // sem_destroy(&s2);
    return 0;
}

/*
Take X, Y, Z, W from the user. Use semaphore to implement the
following Program:
Thread T1
Input (X,Y):
X1= Z+2;
Y1=Z1*5;
S1=X1+Y1;
Printf(“x=%d”,S1);

Thread T2
Input (W,Z):
Z1= X1*2;
W1=Y1+5;
S2=Z1+W1;
Printf(“x=%d”,S2);
*/