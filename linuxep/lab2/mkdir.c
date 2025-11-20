#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void mkdir_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: mkdir <directory_name>\n");
        return;
    }
    int i = 1;
    for (i; i < argc; i++) {
        if (mkdir(argv[i], 0755) == 0) {
            printf("Created directory: '%s'\n", argv[i]);
        } else {
            printf("mkdir: cannot create directory '%s'\n", argv[i]);
        }
    }
}