#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER 500

struct numbers{
    int sum;
    int diff;
    float divis;
    int mult;
};

int main(void){
    int n, fd1, fd2;
    int first, second;
    struct numbers num;

    mkfifo("/tmp/fifo_ans", 0660);
    fd1 = open("/tmp/fifo_req", O_WRONLY);
    printf("Opened request fifo\n");
    fd2 = open("/tmp/fifo_ans", O_RDONLY);
    printf("Opened answer +fifo\n");
    
    printf("Write two numbers: \n");
    scanf("%d", &first);
    scanf("%d", &second);
    write(fd1, &first, BUFFER);
    write(fd1, &second, BUFFER);
    read(fd2, &num, BUFFER);
    printf("Sum: %d, Difference: %d, Division: %f, Multiplication: %d\n", num.sum, num.diff, num.divis, num.mult);
    close(fd1);
    close(fd2);

    return 0;
}