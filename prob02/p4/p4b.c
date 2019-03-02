#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF 256

struct student
{ 
    unsigned char *name;
    int grade;    
};


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
    struct student new_student;
    new_student.name = malloc(50);

    while((nr = read(STDIN_FILENO, buffer, BUFF))){
        if(nr <= 1)
            break;
        new_student.name = buffer;
        if(read(STDIN_FILENO, buffer, BUFF)){
            new_student.grade = atoi(buffer);
            if((nw = write(fd, new_student.name, strlen(new_student.name))) <= 0 ){
                perror(argv[1]);
                close(fd);
                return 2;
            }
        }
    }

    close(fd);
    return 0;
     
}