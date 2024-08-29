/**
 * Problem Statement:
 * Write a program that implements solution to Producer – Consumer problem using mutex and semaphores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void *consumer() {
    while (true) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Consume an item
        int item = buffer[--count];
        printf("Consumer consumed %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(5);
    }
}

void *producer() {
    while (true) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Produce an item
        int item = rand() % 100;
        buffer[count++] = item;
        printf("Producer produced %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

int main() {
    pthread_t prodThread, consThread;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
