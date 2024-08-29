#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;

    if (argc < 2) {
        printf("\nERROR: Directory name not specified...\n");
        exit(EXIT_FAILURE);
    } else if ((dp = opendir(argv[1])) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    } else {
        while ((dirp = readdir(dp)) != NULL) {
            printf("%s\t", dirp->d_name);
        }
        printf("\n");

        closedir(dp);
    }
}
