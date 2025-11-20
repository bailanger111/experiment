#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void parse_input(char *input, int *argc, char *argv[]) {
    *argc = 0;
    
    // 移除换行符
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    // 使用 strtok 分割参数
    char *token = strtok(input, " \t");
    while (token != NULL && *argc < MAX_ARGS - 1) {
        argv[(*argc)++] = token;
        token = strtok(NULL, " \t");
    }
    argv[*argc] = NULL;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *argv[MAX_ARGS];
    int argc;
    
    printf("Simple Shell - Type 'exit' to quit\n");
    printf("Available commands: ls, echo, cat, mkdir, rm, cd, pwd, wc\n");
    
    while (1) {
        printf("myshell> ");
        fflush(stdout);
        
        // 读取输入
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }
        
        // 解析输入
        parse_input(input, &argc, argv);
        
        // 如果没有输入，继续循环
        if (argc == 0) {
            continue;
        }
        
        // 信息：显示解析到的命令和参数
        printf("Command='%s'\n", argv[0]);
    
        // 执行命令
        if (strcmp(argv[0], "exit") == 0) {
            break;
        } else if (strcmp(argv[0], "ls") == 0) {
            ls_command(argc, argv);
        } else if (strcmp(argv[0], "echo") == 0) {
            echo_command(argc, argv);
        } else if (strcmp(argv[0], "cat") == 0) {
            cat_command(argc, argv);
        } else if (strcmp(argv[0], "mkdir") == 0) {
            mkdir_command(argc, argv);
        } else if (strcmp(argv[0], "rm") == 0) {
            rm_command(argc, argv);
        } else if (strcmp(argv[0], "cd") == 0) {
            cd_command(argc, argv);
        } else if (strcmp(argv[0], "pwd") == 0) {
            pwd_command(argc, argv);
        } else if (strcmp(argv[0], "wc") == 0) {
            wc_command(argc, argv);
        } else {
            printf("Command not found: %s\n", argv[0]);
        }
        printf("----------------------------------------\n");
    }
    
    printf("Goodbye!\n");
    return 0;
}