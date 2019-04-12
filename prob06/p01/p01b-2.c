// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
#define NUMITER 100007


void * thrfunc(void * arg)
{
    int i;
    char buffer[10];
    fprintf(stderr, "Starting thread %s\n", arg);
    for (i = 1; i <= NUMITER; i++) write(STDERR,arg,1);
    return NULL;
}
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Invalid parameters: p01b-1 char1 char2");
        exit(1);
    }
    
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, argv[1]);
    pthread_create(&tb, NULL, thrfunc, argv[2]);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}