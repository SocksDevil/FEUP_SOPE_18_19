#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 50
#define ARGS 20

int main(int argc, char *argv[], char *envp[]){
    char buffer[BUFF];
    char * arguments[ARGS] = {NULL};
    char exitWord[] = "quit";
    printf("minish >");
    while(1 > 0){
        fgets(buffer, sizeof(buffer), stdin);
        if(strcmp(buffer, exitWord) == 0)
            break;
        char * tok;
        tok = strtok(buffer, " ");
        arguments[0] = tok;
        int i = 1;
        for(i; i < ARGS; i++)
        {
            tok = strtok(NULL, " ");
            if(tok == NULL)
            {
                arguments[i] = NULL;
                break;
            }
            arguments[i] = tok;
        }
        arguments[i - 1][strlen(arguments[i - 1]) - 1] = '\0';
        for(int i = 0; i < ARGS; i++)
        {
            if(arguments[i] == NULL)
                break;
            printf("%d - %s\n",i, arguments[i]);
        }
        if(fork() > 0){
            int status;
            wait(&status);
            printf("\nminish >");
        }
        else
        {
            execvp(arguments[0], arguments);
            printf("Failed to execute!\n");
            exit(1);
        }    
    }
    return 0;    
}