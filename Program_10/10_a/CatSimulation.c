#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\nError: Invalid number of arguments...\n");
        exit(EXIT_FAILURE);
    } else {
        FILE *fp = fopen(argv[1], "r");

        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        } else {
            char ch;
            while ((ch = fgetc(fp)) != EOF) {
                printf("%c", ch);
            }

            printf("\n");
        }

        fclose(fp);
    }
}
