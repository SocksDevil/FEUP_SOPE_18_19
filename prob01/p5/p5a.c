#define MAX_ARGUMENTS 5000 
#include<stdio.h>

int main(int argc, char **argv, char **envp)
{
    for(int i = 0; i < MAX_ARGUMENTS; i++)
    {
        if(envp[i] == NULL)
            break;
        
        printf("%s\n", envp[i]);
    }    
    return 0;
}