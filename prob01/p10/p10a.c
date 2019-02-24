#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER      50

int main(){
    const char pipe[2] = "|";
    const char and[2] = ";";
    char * str = malloc(MAX_BUFFER);
    fgets(str, MAX_BUFFER, stdin);
    if(strtok(str, pipe) != NULL)
    {
        char * token;
        token = strtok(str, pipe);
        while(token != NULL){
            printf("%s\n", token);
            token = strtok(NULL, pipe);
        }
        
    }
    else
    {
        char * token;
        token = strtok(str, and);
        while(token != NULL){
            printf("%s\n", token);
            token = strtok(NULL, and);
        }
    }
    
}