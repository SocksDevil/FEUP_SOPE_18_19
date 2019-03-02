#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFF 256

int main(int argc, char *argv[]){
    int fd, nr, nw;
    unsigned char buffer[BUFF];
    if(argc != 2){
        printf("Usage %s filename", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL);
    if(fd == -1)
    {
        perror(argv[1]);
        return 3;
    }

    while((nr = read(STDIN_FILENO, buffer, BUFF))){
        if(nr <= 1)
            break;
        if((nw = write(fd, buffer, nr)) <= 0 || nw != nr){
            perror(argv[1]);
            close(fd);
            return 2;
        }
    }

    close(fd);
    return 0;
    
}