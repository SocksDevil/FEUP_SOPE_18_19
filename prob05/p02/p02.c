#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER 512
#define READ    0
#define WRITE   1

struct numbers
{
    int sum;
    int diff;
    float divis;
    int mult;
};


int main(void){
    int n, fd1[2], fd2[2];
    pid_t pid;
    pipe(fd1);
    pipe(fd2);
    int first, second;
    char line[BUFFER];
    struct numbers num;
    if(fork() > 0){
        close(fd1[READ]);
        close(fd2[WRITE]);
        printf("Write two numbers: \n");
        scanf("%s", line);        
        write(fd1[WRITE], line, sizeof(line));        
        scanf("%s", line);
        write(fd1[WRITE], line, sizeof(line));        
        read(fd2[READ], &num, BUFFER);
        printf("Sum: %d, Difference: %d, Division: %f, Multiplication: %d\n", num.sum, num.diff, num.divis, num.mult);
    }
    else{
        close(fd1[WRITE]);
        close(fd2[READ]);
        n = read(fd1[READ], line, BUFFER);
        first = atoi(line);
        n = read(fd1[READ], line, BUFFER);
        second = atoi(line);
        num.sum = first + second;
        num.diff = first - second;
        num.divis = first/(double) second;
        num.mult = first * second;
        write(fd2[WRITE], &num, sizeof(num));
    }
    
}