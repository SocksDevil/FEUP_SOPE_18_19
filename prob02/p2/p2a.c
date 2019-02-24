#include <stdio.h>
#include <stdlib.h>
#define BUFF 256


int main(int argc, char **argv)
{
    FILE * infile, *outfile;
    char buffer [BUFF];
    if(argc != 3)
    {
        printf("Usage: %s file1 file2", argv[0]);
        exit(1);
    }

    if ( (infile = fopen(argv[1], "r"))  == NULL)
    {
        perror("Error");
        exit(2);
    }
    if (( outfile = fopen(argv[2], "w")) == NULL)
    {
        perror("Error");
        exit(3);        
    }

    while( (fgets(buffer, BUFF, infile)) != NULL){
        fputs(buffer, outfile);
    }
    fclose(infile);
    fclose(outfile);
    exit(0);  

}