#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <ctype.h>  

void removeNonAlphabets(char * inputFileName, char * outputFileName)
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen(inputFileName, "r");
    fp2 = fopen(outputFileName, "w");
    while ((ch = fgetc(fp1)) != EOF)
    {
            fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char *argv[])
{
    removeNonAlphabets(argv[1], argv[2]);
    return 0;
}

