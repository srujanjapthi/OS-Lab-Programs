/**
 * Problem Statement:
 * Write a program to simulate grep command using system calls.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\nError: Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    } else {
        FILE *fp = fopen(argv[2], "r");
        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char temp[100];
        while (!feof(fp)) {
            fgets(temp, 100, fp);
            if (strstr(temp, argv[1])) {
                printf("%s", temp);
            }
        }

        fclose(fp);
    }
}
