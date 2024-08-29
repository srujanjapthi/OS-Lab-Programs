/**
 * Problem Statement:
 * Write a program that implements solution to Readers-Writers problem using rw_mutex and semaphores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t rw_mutex;
sem_t writeSem;
int readersCount;

void *reader() {
    while (true) {
        pthread_mutex_lock(&rw_mutex);
        if (++readersCount == 1) {
            sem_wait(&writeSem);
        }
        pthread_mutex_unlock(&rw_mutex);

        printf("Reader is reading...\n");
        sleep(1);

        pthread_mutex_lock(&rw_mutex);
        if (--readersCount == 0) {
            sem_post(&writeSem);
        }
        pthread_mutex_unlock(&rw_mutex);

        sleep(1);
    }
}

void *writer() {
    while (true) {
        sem_wait(&writeSem);

        printf("Writer is writing...\n");
        sleep(1);

        sem_post(&writeSem);

        sleep(1);
    }
}

int main() {
    pthread_t readerThread1, readerThread2, writerThread;

    pthread_mutex_init(&rw_mutex, NULL);
    sem_init(&writeSem, 0, 1);

    pthread_create(&readerThread1, NULL, reader, NULL);
    pthread_create(&readerThread2, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);

    pthread_join(readerThread1, NULL);
    pthread_join(readerThread2, NULL);
    pthread_join(writerThread, NULL);

    pthread_mutex_destroy(&rw_mutex);
    sem_destroy(&writeSem);
}
