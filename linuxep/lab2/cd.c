#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void cd_command(int argc, char *argv[]) {
    char *path = argc > 1 ? argv[1] : getenv("HOME");
    
    if (path == NULL) {
        path = ".";
    }
    
    if (chdir(path) != 0) {
        perror("cd");
    }
}