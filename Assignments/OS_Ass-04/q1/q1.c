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
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


// Global variables
int potentialCPatients = 0;
sem_t coronaPatient;
sem_t fluPatient;
sem_t mutex;
sem_t printing;
int TEST = 2;

// Function prototypes
void *_patient(void *arg);
bool testPatient();
void coronaPatientRecovery();
void fluPatientRecovery();


int main()
{
    // Local variables
    int i, N;
    

    /* extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value) */
    sem_init(&coronaPatient, 0, 0);
    sem_init(&fluPatient, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&printing, 0, 1);

    printf("Enter the number of potential patients: ");
    scanf("%d", &N);
    pthread_t tid[N];

    for (i = 0; i < N; i++){
        pthread_create(&tid[i], NULL, _patient, NULL);
        sem_wait(&mutex);
        potentialCPatients++;
        sem_wait(&printing);
        printf("Potential patient %d has entered the hospital for testing. Total potential patients: %d \n", i+1, potentialCPatients);
        sem_post(&printing);
        sem_post(&mutex);
    }
    // Join N threads
    for (i = 0; i < N; i++){
        pthread_join(tid[i], NULL);
    }
    // Destroy semaphores
    sem_destroy(&coronaPatient);
    sem_destroy(&fluPatient);
    sem_destroy(&mutex);
    sem_destroy(&printing);
    return 0;
}

// Function definitions
void *_patient(void *arg){

    bool infected = false;

    infected = testPatient();

    if (infected){
        sem_wait(&mutex);
        potentialCPatients--;

        
        sem_wait(&printing);
        printf("Patient is infected with coronavirus. Total potential patients: %d \n", potentialCPatients);
        sem_post(&printing);

        sem_post(&coronaPatient);
        sem_post(&mutex);       
    }
    // If patient is not infected
    else{
        sem_wait(&mutex);
        potentialCPatients--;

        sem_wait(&printing);
        printf("Patient is infected with flu. Total potential patients: %d \n", potentialCPatients);
        sem_post(&printing);

        sem_post(&fluPatient);
        
        sem_post(&mutex);
    }

    if (infected){
        coronaPatientRecovery();
    }

    else{
        fluPatientRecovery();
    }
    pthread_exit(NULL);
}

bool testPatient(){

    bool infected = false;
    srand(time(NULL));
    int random = rand() % 2;    // 0/1
    if (random == 0){
        infected = true;
    }else{
        infected = false;
    }
    sem_wait(&mutex);
    if (TEST == 0)
        infected = false;
    sem_post(&mutex);
    return infected;
}

void coronaPatientRecovery(){

    bool infected = true;

    infected = testPatient();

    if (infected){
        printf("Patient is still infected with coronavirus. \n");
        // decrementing TEST counter
        sem_wait(&mutex);
        TEST--;
        sem_post(&mutex);
        coronaPatientRecovery();
    }
    else{
        printf("Patient is no longer infected with coronavirus. \n");
        sem_wait(&coronaPatient);
    }
}

void fluPatientRecovery(){
    // Wait for fluPatient semaphore
    sem_wait(&fluPatient);
    sem_wait(&printing);
    printf("Patient is no longer infected with flu. \n");
    sem_post(&printing);
    sem_post(&fluPatient);  
}