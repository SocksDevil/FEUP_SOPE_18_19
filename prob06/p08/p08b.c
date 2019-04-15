#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_ARGUMENTS 10

void * grep_file(void * args){
    char ** argv = (char **) args;

    FILE * fp;

    fp = fopen(argv[0], "r");
    if (fp == NULL){
        printf("Failed to open file :%s!\n", argv[0]);
        exit(1);
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if(strstr(line, argv[1]) != NULL)
            printf("Found %s at line %d of file %s!\n", argv[1], i, argv[0]);
        printf("%s", line);
        i++;
    }
    printf("\n");
    if (line)
        free(line);
    free(args);
    pthread_exit(0);
}

int main(int argc, char * argv[])
{
    if(argc < 3){
        printf("Usage: grep_mt string filename1, filename2....\n");
        exit(1);
    }
    for(int i = 2; i < MAX_ARGUMENTS; i++){
        if(argv[i] == NULL)
            break;
        char ** arguments = malloc(2 * sizeof(char *));
        arguments[0] = argv[i];
        arguments[1] = argv[1]; 
        pthread_t tid;
        pthread_create(&tid, NULL, grep_file, arguments); 
    } 

    pthread_exit(0);
}