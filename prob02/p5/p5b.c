#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main(void)
{
    int fd;
    char *text1="CCCCC";
    char *text2="DDDDD";
    fd = open("f1.txt", O_WRONLY|O_SYNC|O_APPEND,0600);
    if(fd == -1){
        perror("f1.txt");
        return 1;
    }
    getchar();
    write(fd,text1,5);
    write(fd,text2,5);
    close(fd);
    return 0;
}
