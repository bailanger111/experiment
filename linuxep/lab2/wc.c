#include <stdio.h>
#include <ctype.h>

void wc_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: wc <filename>\n");
        return;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("wc");
        return;
    }
    
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        chars++;
        
        if (ch == '\n') {
            lines++;
        }
        
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    
    fclose(file);
    
    printf(" %d %d %d %s\n", lines, words, chars, argv[1]);
}