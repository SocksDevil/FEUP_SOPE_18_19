#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF 50
#define ARGS 20

int main(int argc, char *argv[], char *envp[]){
    char buffer[BUFF];
    int stdout = dup(1);
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
            if(tok == NULL){
                arguments[i] = NULL;
                arguments[i - 1][strlen(arguments[i - 1]) - 1] = '\0';
                break;
            }
            else if(strcmp(tok, "-o") == 0){
                tok = strtok(NULL, " ");
                arguments[i] = NULL;
                if(tok == NULL){
                    printf("No file was appointed, writing to screen\n");
                    break;
                }else
                {
                    tok[strlen(tok) - 1] = '\0';
                    int fd = open(tok, O_WRONLY | O_CREAT, 0600);
                    dup2(fd, STDOUT_FILENO);
                    break;
                }
                
            }
            arguments[i] = tok;
        }
        if(fork() > 0){
            int status;
            wait(&status);
            dup2(stdout, STDOUT_FILENO);
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