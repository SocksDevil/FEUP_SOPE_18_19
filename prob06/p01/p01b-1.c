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
    sprintf(buffer, "%d", *(int *) arg);
    fprintf(stderr, "Starting thread %d\n", *(int *) arg);
    for (i = 1; i <= NUMITER; i++) write(STDERR,buffer,1);
    return NULL;
}
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Invalid parameters: p01b-1 int1 int2");
        exit(1);
    }
    
    pthread_t ta, tb;
    int a, b;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    pthread_create(&ta, NULL, thrfunc, &a);
    pthread_create(&tb, NULL, thrfunc, &b);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}