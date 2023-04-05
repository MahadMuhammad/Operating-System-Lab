/*  21L-6195 Muhammad Mahad
Help the world in crisis by developing a Coronavirus (COVID-19) management system.
You are required to manage the number of coronavirus patients via threads and semaphores.
Suppose N number of potential Corona patients enter the hospital. You will have to write a
program that initializes N threads simultaneously where each thread increments a shared variable
potentialCPatients. After tests are being carried out for each potential patient, a patient may
either be infected or not infected by coronoavirus in a random fashion. If the patient is infected, a
semaphore called coronaPatient will be signaled/incremented. Whereas if the patient is NOT
infected, a semaphore called fluPatient will be signaled/incremented. In either case, the shared
variable called potentialCpatient variable will be decremented. You are not concerned with the
recovery of the flu patients but only with the coronavirus patients. Eventually, each corona
patient has to get better. For this purpose, each corona patient will go through tests and wait will
be called for the coronaPatient only after two consecutive tests return false.
NOTE: Create necessary functions to enhance code readability. Also, N must be taken as user
input.
*/
#include <stdio.h>  // for printf
#include <stdlib.h> // for rand
#include <pthread.h> // for pthread_create
#include <semaphore.h> // for sem_init
#include <unistd.h> // for sleep
#include <stdbool.h> // for bool
#include <time.h> // for time

// Global variables
int potentialCPatients = 0;
int coronaPatient = 0;
int fluPatient = 0;
int totalCPatients = 0;

// atomic wait
void wait(int *sem) {
    while (*sem <= 0) {

    } // busy wait
    *sem = *sem - 1;
}

// atomic signal
void signal(int *sem) {
    *sem = *sem + 1;
}

// function to check if patient is infected
bool isInfected() {
    int random = rand() % 2;
    if (random == 0) {
        return true;
    } else {
        return false;
    }
}

// function to check if patient is recovered
bool isRecovered() {
    int random = rand() % 2;
    if (random == 0) {
        return true;
    } else {
        return false;
    }
}

// test function
void test() {
    int random = rand() % 2;
    if (random == 0) {
        printf("Test result: Positive\n");
    } else {
        printf("Test result: Negative\n");
    }
}

int main()
{
    srand(time(NULL));

    printf("Enter number of potential patients: ");
    scanf("%d", &potentialCPatients);

    pthread_t threads[potentialCPatients];

    for (int i = 0; i < potentialCPatients; i++) {
        pthread_create(&threads[i], NULL, (void *) &test, NULL);
    }
    // wait for threads to finish
    for (int i = 0; i < potentialCPatients; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n----- MAIN END -----\n")
    return 0;
}


