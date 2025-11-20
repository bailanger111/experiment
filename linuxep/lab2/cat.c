#include <stdio.h>
#include <stdlib.h>

void cat_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cat <filename>\n");
        return;
    }
    int i = 1;
    for (i; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("cat: cannot open '%s'\n", argv[i]);
            continue;
        }
        
        printf("=== Content of %s ===\n", argv[i]);
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        printf("=== End of %s ===\n", argv[i]);
        
        fclose(file);
    }
}