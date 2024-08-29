#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\nError: Invalid number of arguments...\n");
        exit(EXIT_FAILURE);
    } else {
        FILE *fp1 = fopen(argv[1], "r");
        FILE *fp2 = fopen(argv[2], "a");

        if (fp1 == NULL || fp2 == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        } else {
            char ch;
            while ((ch = fgetc(fp1)) != EOF) {
                fprintf(fp2, "%c", ch);
            }

            fprintf(fp2, "\n");
        }

        fclose(fp1), fclose(fp2);
    }
}
