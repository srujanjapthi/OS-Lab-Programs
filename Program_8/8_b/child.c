#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct {
    int n, arr[25];
} pack_t;

int main() {
    int shm_id = shm_open("FIB", O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    pack_t *psm = (pack_t *)mmap(NULL, sizeof(pack_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (psm == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("[CHILD] Shared memory is attached at: %p\n", psm);
    printf("[CHILD] Generating Fibonacci numbers...\n");

    psm->arr[0] = 0, psm->arr[1] = 1;
    for (int i = 2; i < psm->n; i++) {
        psm->arr[i] = psm->arr[i - 1] + psm->arr[i - 2];
    }

    printf("[CHILD] Fibonacci numbers generated successfully\n");

    return EXIT_SUCCESS;
}
