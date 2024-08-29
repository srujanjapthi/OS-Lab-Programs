/**
 * Write a program to generate and print Fibonacci series with the following requirements:
 * - Parent program should create a child and distribute the task of generating Fibonacci no to its child.
 * - The code for generating Fibonacci series should reside in different program.
 * - Child should write the generated Fibonacci series to a shared memory.
 * - Parent process has to print by retrieving the Fibonacci series from the shared memory.
 * Implement the above using shmget and shmat.
 * Note: Shared object should be removed at the end in the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

typedef struct {
    int n, arr[25];
} pack_t;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }

    key_t key = ftok("child.c", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shm_id = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pack_t *shm_ptr = (pack_t *)shmat(shm_id, NULL, 0666);
    if (shm_ptr == (pack_t *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("[PARENT] Created shared memory with key = %d, ID = %d, Address = %p\n", key, shm_id, shm_ptr);
    shm_ptr->n = atoi(argv[1]);

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (!child_pid) {
        execlp("./child", "./child", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("\n[PARENT] Child finished executing\n");
        printf("[PARENT] The first %d Fibonacci numbers are:\n", shm_ptr->n);
        for (int i = 0; i < shm_ptr->n; i++) {
            printf("%d ", shm_ptr->arr[i]);
        }
        printf("\n");
    }

    if (shmdt((void *)shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    printf("[PARENT] Shared memory deleted.\n");
    return 0;
}
