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
    pid_t pid;
};

int main(void){
    int fd1, fd2;
    int first, second;
    pid_t n;
    struct numbers num;
    char answer_fifo[BUFFER];
    n = getpid();
    sprintf(answer_fifo, "/tmp/fifo_ans_%u", n);
    fd1 = open("/tmp/fifo_req", O_WRONLY);
    printf("Opened request fifo\n");
    printf("Opened answer fifo\n");
    printf("Write two numbers: \n");
    scanf("%d", &first);
    scanf("%d", &second);
    write(fd1, &first, BUFFER);
    write(fd1, &second, BUFFER);
    write(fd1, &n, BUFFER);
    printf("Opening fifo %s\n", answer_fifo);
    mkfifo(answer_fifo, 0660);
    fd2 = open(answer_fifo, O_RDONLY);
    read(fd2, &num, BUFFER);
    printf("Sum: %d, Difference: %d, Division: %f, Multiplication: %d\n", num.sum, num.diff, num.divis, num.mult);
    close(fd1);
    close(fd2);
    return 0;
}