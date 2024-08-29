/**
 * Write a program to generate and print Prime nos. between a given range (between M & N) with the following requirements:
 * - M & N should be passed as command line arguments.
 * - Error checking should be done to verify the required no. of arguments at the command line.
 * - Parent program should create a child and distribute the task of generating Prime numbers to its child.
 * - The code for generating Prime numbers should reside in different program.
 * - Child should write the generated Prime numbers to a shared memory.
 * - Parent process has to print the Prime numbers by retrieving from the shared memory.
 * Implement the above using shm_open and mmap.
 * Note: Shared object should be removed at the end in the program. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct {
    int m, n;
    int prime_count;
    int primes[100];
} pack_t;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\nError: Invalid number of arguments...\n");
        exit(EXIT_FAILURE);
    }

    int shm_id = shm_open("PRIME", O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_id, sizeof(pack_t)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    pack_t *psm = (pack_t *)mmap(NULL, sizeof(pack_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (psm == (pack_t *)(-1)) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    psm->m = atoi(argv[1]);
    psm->n = atoi(argv[2]);

    printf("\n[PARENT] Attached to shared memory at the address %p\n", psm);
    printf("[PARENT] Waiting for child to generate prime numbers...\n");

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
        printf("\n[PARENT] Child completed generating prime numbers...\n");
        printf("[PARENT] Prime numbers in the range [%d - %d]: ", psm->m, psm->n);
        for (int i = 0; i < psm->prime_count; i++) {
            printf("%d ", psm->primes[i]);
        }
        printf("\n");
    }

    if (shm_unlink("PRIME") == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }
}
