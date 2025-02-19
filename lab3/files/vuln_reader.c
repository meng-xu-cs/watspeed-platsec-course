#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Program %s does not take arguments\n", argv[0]);
        exit(1);
    }

    const char *filename = "target.txt";
    char target[256];

    // Find the target of the symbolic link
    ssize_t len = readlink(filename, target, sizeof(target));
    if (len == -1) {
        perror("readlink");
        exit(1);
    }
    target[len] = '\0';

    // Check if the target being accessed is "safe.txt"
    if (strcmp(target, "safe.txt") != 0) {
        fprintf(stderr, "Invalid symbolic link %s\n", target);
        exit(1);
    }

    // Introduce an artificial delay to widen the race window.
    usleep(100000);

    // Open and read the symbolic link
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(fp);
    return 0;
}
