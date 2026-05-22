#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

int N;

#define THINKING 0
#define EATING 1

int *state;
pthread_mutex_t mutex;
sem_t *S;

// Function to check if philosopher can eat
void test(int phnum) {

    if (state[(phnum + N - 1) % N] != EATING &&
        state[(phnum + 1) % N] != EATING) {

        state[phnum] = EATING;

        printf("Philosopher %d picked up left fork %d.\n",
               phnum, phnum);

        printf("Philosopher %d picked up right fork %d.\n",
               phnum, (phnum + 1) % N);

        printf("Philosopher %d is eating.\n", phnum);

        sem_post(&S[phnum]);
    }
}

// Take forks
void take_fork(int phnum) {

    pthread_mutex_lock(&mutex);

    test(phnum);

    pthread_mutex_unlock(&mutex);

    sem_wait(&S[phnum]);

    sleep(1);
}

// Put forks
void put_fork(int phnum) {

    pthread_mutex_lock(&mutex);

    state[phnum] = THINKING;

    printf("Philosopher %d put down forks %d and %d.\n",
           phnum, phnum, (phnum + 1) % N);

    printf("Philosopher %d is thinking.\n", phnum);

    // Check neighbors
    test((phnum + N - 1) % N);
    test((phnum + 1) % N);

    pthread_mutex_unlock(&mutex);
}

// Philosopher function
void* philosopher(void* num) {

    int phnum = *(int*)num;

    while (1) {

        printf("Philosopher %d is thinking.\n", phnum);

        sleep(1);

        take_fork(phnum);

        sleep(2);

        put_fork(phnum);
    }
}

int main() {

    int i;

    printf("Enter number of philosophers: ");
    scanf("%d", &N);

    pthread_t thread_id[N];
    int phil[N];

    state = (int*)malloc(N * sizeof(int));
    S = (sem_t*)malloc(N * sizeof(sem_t));

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
        state[i] = THINKING;
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {

        phil[i] = i;

        pthread_create(&thread_id[i], NULL,
                       philosopher, &phil[i]);
    }

    // Join threads
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    free(state);
    free(S);

    return 0;
}
