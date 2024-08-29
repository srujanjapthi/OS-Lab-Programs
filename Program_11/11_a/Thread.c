/**
 * Problem Statement:
 * Write a program with two threads and a main thread. Schedule the task of calculating the natural sum upto ‘n’ terms and factorial of 'n' on these threads.
 * Note: The main thread should read ‘n’ from command line and pass it as parameter to remaining threads. Terminate the threads using system calls.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0, fact = 1;

void *add(void *params) {
    int n = atoi((char *)params);
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("Add Thread completed...\n");
}

void *factorial(void *params) {
    int n = atoi((char *)params);
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }

    printf("Factorial Thread completed...\n");
}

void main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("ERROR: Invalid Arguments");
        exit(EXIT_FAILURE);
    }

    pthread_t t1, t2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&t1, &attr, add, argv[1]);
    pthread_create(&t2, &attr, factorial, argv[1]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Inside main Thread\n");
    printf("Sum = %d\n", sum);
    printf("Factorial = %d\n", fact);
}
