#include <string.h>
#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h> 

int main(int argc, char *argv[]){
    char prog[20];
    sprintf(prog,"%s.c",argv[1]);
    execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL);
    printf("Error!\n");
    exit(1);
}