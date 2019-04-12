#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>

struct file_info{
    struct dirent direntp;
    struct stat stat_buf;
    char *buffer;
};

void * copy_file(void * arg){
    struct file_info *info = (struct file_info * ) arg;
    printf("Copying file %s\n", info->direntp.d_name);
    if (S_ISREG(info->stat_buf.st_mode)){
        execlp("cp", "cp", info->direntp.d_name, info->buffer, NULL);
    } 
    else if (S_ISDIR(info->stat_buf.st_mode)){
        if(strcmp(info->direntp.d_name, ".") != 0 || strcmp(info->direntp.d_name, "..") != 0)
        {
            execlp("mkdir", "mkdir", info->direntp.d_name, info->buffer, NULL);
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char buffer[512];

    if ((dirp = opendir( argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    getcwd(buffer, 512);
    if(strcmp(argv[2], ".") == 0)
        strcat(buffer, argv[2]);
    printf("Path: %s\n", buffer);
    chdir(argv[1]);
    while ((direntp = readdir( dirp)) != NULL)
    {
        if(stat(direntp->d_name, &stat_buf) == 0){
            pthread_t tid;
            struct file_info * info = malloc(sizeof(struct file_info));
            info->direntp = *direntp;
            info->stat_buf = stat_buf;
            info->buffer = buffer;
            pthread_create(&tid, NULL, copy_file, buffer);
            pthread_detach(tid);
        }
    }
    closedir(dirp);
    exit(0);
}
