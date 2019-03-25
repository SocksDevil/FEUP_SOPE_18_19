#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER 512
#define READ    0
#define WRITE   1

int main(int argc, char * argv[]){
    int fd[2], n;
    char buffer[BUFFER];
    pipe(fd);

    if(fork() > 0){
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        execlp("sort", "sort");
        printf("Failed to execute sort!\n");
        exit(1);   
    }
    else{
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        execlp("cat", "cat", argv[1]);
        printf("Failed to execute cat!\n");
        exit(1);
    }
    return 0;
}