#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char *str;
    unsigned char buffer[512];
    if (argc != 2)
    {
        fprintf( stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }
    if ((dirp = opendir( argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    printf("%s\n", getcwd(buffer, 512));
    chdir(argv[1]);
    while ((direntp = readdir( dirp)) != NULL)
    {
        if(stat(direntp->d_name, &stat_buf) == 0){
            printf("%-10d - ", (int) stat_buf.st_ino);
            if (S_ISREG(stat_buf.st_mode)) str = "regular";
            else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
            else str = "other";
            printf("%-25s - %s\n", direntp->d_name, str);
        }
    }
    closedir(dirp);
    exit(0);
}
