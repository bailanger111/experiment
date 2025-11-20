#include <stdio.h>

void echo_command(int argc, char *argv[]) {
    // 如果没有参数，只输出换行
    if (argc == 1) {
        printf("\n");
        return;
    }
    
    // 输出所有参数
    int i = 1;
    for (i; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
}