#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ARGUMENTS 5000 
#define MAX_NAME      50

int main(int argc, char **argv, char **envp)
{
    char * name = malloc(MAX_NAME);
    char * cmp = "USERNAME";
    for(int i = 0; i < MAX_ARGUMENTS; i++)
    {
        if(strncmp(cmp, envp[i], 8) == 0)
        {
            memcpy(name, envp[i] + 9, MAX_NAME);
            break;
        }
    }

    printf("Hello %s!\n", name);
    return 0;
} 