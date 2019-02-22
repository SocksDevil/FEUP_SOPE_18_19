#include <stdio.h>
#include <stdlib.h>

void exit_func_1(){
    printf("Executing handler 1\n");
}

void exit_func_2(){
    printf("Executing handler 2\n");
}

int main(){
    atexit(exit_func_2); 
    atexit(exit_func_1); 
    printf("Main done!\n");
    return 0;
}