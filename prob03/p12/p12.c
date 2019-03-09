#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char *str;
    unsigned char buffer[512];
    unsigned char *fullpath = malloc(512);

    if ((dirp = opendir( argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    getcwd(buffer, 512);
    if(strcmp(argv[2], "."))
        strcat(buffer, argv[2]);
    printf("Path: %s\n", buffer);
    chdir(argv[1]);
    while ((direntp = readdir( dirp)) != NULL)
    {
        if(stat(direntp->d_name, &stat_buf) == 0){
            if(fork() == 0)
            {
                if (S_ISREG(stat_buf.st_mode)){
                    execlp("cp", "cp", direntp->d_name, buffer, NULL);
                } 
                else if (S_ISDIR(stat_buf.st_mode)){
                    if(strcmp(direntp->d_name, ".") != 0 || strcmp(direntp->d_name, "..") != 0)
                    {
                        execlp("mkdir", "mkdir", direntp->d_name, buffer, NULL);
                    }
                }
                exit(0);
            }
        }
    }
    closedir(dirp);
    exit(0);
}
