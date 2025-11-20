#include <stdio.h>
#include <unistd.h>

void rm_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: rm <filename>\n");
        return;
    }
    int i =1;
    for (i; i < argc; i++) {
        if (unlink(argv[i]) != 0) {
            perror("rm");
        }
    }
}