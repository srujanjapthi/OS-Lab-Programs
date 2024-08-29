#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct {
    int m, n;
    int prime_count;
    int primes[100];
} pack_t;

bool isPrime(int n) {
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int shm_id = shm_open("PRIME", O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    pack_t *psm = (pack_t *)mmap(NULL, sizeof(pack_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (psm == (pack_t *)(-1)) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("\n[CHILD] Attached to shared memory at the address %p\n", psm);
    printf("[CHILD] Generating Prime numbers in the range [%d - %d]\n", psm->m, psm->n);

    psm->prime_count = 0;
    for (int i = psm->m; i <= psm->n; i++) {
        if (isPrime(i)) {
            psm->primes[psm->prime_count++] = i;
        }
    }

    printf("[CHILD] Finished generating prime numbers...\n");
}
