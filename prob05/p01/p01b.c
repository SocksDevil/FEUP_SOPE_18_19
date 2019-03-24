#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER 512
#define READ    0
#define WRITE   1

struct numbers
{
    int first;
    int second;
};


int main(void){
    int n, fd[2];
    pid_t pid;
    pipe(fd);
    int first, second;
    char line[BUFFER];
    struct numbers num;
    if(fork() > 0){
        close(fd[READ]);
        printf("Write two numbers: \n");
        scanf("%d", &num.first);        
        scanf("%d", &num.second);
        write(fd[WRITE], &num, sizeof(num));        
    }
    else{
        close(fd[WRITE]);
        n = read(fd[READ], &num, BUFFER);
        int sum = num.first + num.second;
        int diff = num.first - num.second;
        double division = num.first/(double) num.second;
        int mult = num.first * num.second;
        printf("Sum: %d, Difference: %d, Division: %f, Multiplication: %d\n", sum, diff, division, mult);
    }
    
}