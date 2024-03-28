#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

int counter = 0;
pthread_mutex_t lock;

void *increment_counter(void *thread_id) {
    int tid = *((int *)thread_id);
    pthread_mutex_lock(&lock);
    counter++;
    printf("Thread %d incremented counter to %d\n", tid, counter);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    // Initialize the mutex lock
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, increment_counter, (void *)&thread_ids[i]) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);

    return 0;
}

