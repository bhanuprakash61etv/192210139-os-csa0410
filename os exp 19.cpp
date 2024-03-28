#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, rw_mutex;
int readers_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading shared data: %d\n", reader_id, shared_data);

        // Exit section
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Sleep to simulate reading time
        usleep(100000);
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&rw_mutex);

        // Writing section
        shared_data++;
        printf("Writer %d is writing shared data: %d\n", writer_id, shared_data);

        // Exit section
        sem_post(&rw_mutex);

        // Sleep to simulate writing time
        usleep(2000000);
    }
}

int main() {
    pthread_t reader_threads[NUM_READERS], writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    int i;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Join reader threads
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Join writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

