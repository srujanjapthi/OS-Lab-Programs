#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef struct {
    int n, arr[25];
} pack_t;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }

    int shm_id = shm_open("FIB", O_RDWR | O_CREAT, 0666);
    if (shm_id == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_id, sizeof(pack_t)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    pack_t *psm = (pack_t *)mmap(NULL, sizeof(pack_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (psm == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    psm->n = atoi(argv[1]);

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        execlp("./child", "child", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("[PARENT] Child finished executing\n");
        printf("[PARENT] First %d Fibonacci numbers are: ", psm->n);
        for (int i = 0; i < psm->n; i++) {
            printf("%d ", psm->arr[i]);
        }
        printf("\n");
    }
    
    if (shm_unlink("FIB") == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }
}
