#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void ls_command(int argc, char *argv[]) {
    int long_format = 0;
    char *path = ".";
    
    // 解析参数
    int i =1;
    for (i; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;
        } else {
            path = argv[i];
        }
    }
    
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("ls");
        return;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // 跳过隐藏文件
        if (entry->d_name[0] == '.') {
            continue;
        }
        
        if (long_format) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            
            struct stat file_stat;
            if (stat(full_path, &file_stat) == 0) {
                // 文件类型和权限
                printf("%c", S_ISDIR(file_stat.st_mode) ? 'd' : '-');
                printf("%c", file_stat.st_mode & S_IRUSR ? 'r' : '-');
                printf("%c", file_stat.st_mode & S_IWUSR ? 'w' : '-');
                printf("%c", file_stat.st_mode & S_IXUSR ? 'x' : '-');
                printf("%c", file_stat.st_mode & S_IRGRP ? 'r' : '-');
                printf("%c", file_stat.st_mode & S_IWGRP ? 'w' : '-');
                printf("%c", file_stat.st_mode & S_IXGRP ? 'x' : '-');
                printf("%c", file_stat.st_mode & S_IROTH ? 'r' : '-');
                printf("%c", file_stat.st_mode & S_IWOTH ? 'w' : '-');
                printf("%c", file_stat.st_mode & S_IXOTH ? 'x' : '-');
                
                // 硬链接数
                printf(" %lu", file_stat.st_nlink);
                
                // 所有者和组
                struct passwd *pw = getpwuid(file_stat.st_uid);
                struct group *gr = getgrgid(file_stat.st_gid);
                printf(" %s %s", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");
                
                // 文件大小
                printf(" %8ld", file_stat.st_size);
                
                // 修改时间
                char time_buf[64];
                strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", 
                        localtime(&file_stat.st_mtime));
                printf(" %s", time_buf);
                
                printf(" %s\n", entry->d_name);
            }
        } else {
            printf("%s  ", entry->d_name);
        }
    }
    
    if (!long_format) {
        printf("\n");
    }
    
    closedir(dir);
}