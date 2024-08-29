#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>

typedef struct {
    int n, arr[25];
} pack_t;

int main() {
    key_t key = ftok("child.c", 65);
    if (key == -1) {
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

    printf("\n[CHILD] Attached to shared memory with key = %d, id = %d, Address = %p\n", key, shm_id, shm_ptr);

    shm_ptr->arr[0] = 0, shm_ptr->arr[1] = 1;
    for (int i = 2; i < shm_ptr->n; i++) {
        shm_ptr->arr[i] = shm_ptr->arr[i - 1] + shm_ptr->arr[i - 2];
    }

    printf("[CHILD] Finished generating first %d Fibonacci numbers\n", shm_ptr->n);
    if (shmdt((void *)shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
