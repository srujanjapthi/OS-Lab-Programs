#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>

typedef struct {
    int n, arr[100];
} pack_t;

void main() {
    key_t key = ftok("parent.c", 65);
    if (key == (key_t) (-1)) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shm_id = shmget(key, sizeof(pack_t), 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pack_t *shm_ptr = (pack_t *)shmat(shm_id, NULL, 0666);
    if (shm_ptr == (pack_t *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("\n[CHILD] Generating %d odd numbers.\n", shm_ptr->n);

    shm_ptr->arr[0] = 1;
    for (int i = 1; i < shm_ptr->n; i++) {
        shm_ptr->arr[i] = shm_ptr->arr[i - 1] + 2;
    }

    printf("[CHILD] Completed generating odd numbers.\n");

    if (shmdt((void *)shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("[CHILD] Exiting from Child Process.\n");
}
