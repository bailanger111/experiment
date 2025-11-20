#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pwd_command(int argc, char *argv[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}