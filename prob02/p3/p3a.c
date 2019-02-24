#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFF 256

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        printf("Usage: %s file", argv[0]);
        exit(1);
    }

    int fd, r, wr;
    char buf[BUFF];

    fd = open(argv[1], O_RDONLY);

    if(fd == -1)
    {
        perror(argv[1]);
        exit(2);
    }

    while( (r = read(fd, buf, BUFF)) > 0 && r != 1){
        if((wr = write(STDOUT_FILENO, buf, r))  <= 0 || wr != r){
            perror(argv[1]);
            close(fd);
            exit(3);
        }
    }

    close(fd);
    exit(0);

    
}