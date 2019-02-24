#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFF 256


int main(int argc , char ** argv)
{
    if(argc != 3)
    {
        printf("Usage: %s file1 file2", argv[0]);
        exit(1);
    }

    int fd1, fd2, r, wri;
    char buffer[BUFF];

    fd1 = open(argv[1], O_RDONLY);

    if(fd1 == -1)
    {
        perror(argv[1]);
        exit(2);
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);

    if(fd2 == -1)
    {
        perror(argv[2]);
        close(fd1);
        exit(3);
    }

    while( (r = read(fd1, buffer, BUFF)) > 0 ){
        if((wri = write(fd2, buffer, r)) <= 0 || wri != r){
            perror(argv[2]);
            close(fd1);
            close(fd2);
            exit(4);
        }
    }
    close(fd1);
    close(fd2);
    exit(0);
}