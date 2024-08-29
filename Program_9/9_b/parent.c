/**
 * Write a program to generate and print N ODD numbers with the following requirements:
 * - Parent program should create a child and distribute the task of generating odd numbers to its child.
 * - The code for generating odd numbers should reside in different program.
 * - Child should write the generated odd numbers to a shared memory.
 * - Parent process has to print the odd numbers by retrieving from the shared memory.
 * Implement the above using shmget and shmat.
 * Note: Shared object should be removed at the end in the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>

typedef struct {
    int n, arr[100];
} pack_t;

void main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\nError: Invalid number of arguments...\n");
        exit(EXIT_FAILURE);
    }

    key_t key = ftok("parent.c", 65);
    if (key == (key_t)(-1)) {
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

    shm_ptr->n = atoi(argv[1]);

    printf("\n[PARENT] Waiting for Child Process to generate odd numbers.\n");

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        execlp("./child", "./child", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("\n[PARENT] Child finished executing\n");
        printf("[PARENT] First %d odd numbers are: ", shm_ptr->n);

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
}
