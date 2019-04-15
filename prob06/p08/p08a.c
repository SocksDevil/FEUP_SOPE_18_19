#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    if(argc != 3){
        printf("Usage: grep_m string filename\n");
        exit(1);
    }
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        printf("Failed to open file!\n");
        exit(1);
    }
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if(strstr(line, argv[1]) != NULL)
            printf("Found %s at line %d!\n", argv[1], i);
        printf("%s", line);
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(0);
}