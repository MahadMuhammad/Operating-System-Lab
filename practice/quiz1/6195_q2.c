/*
    Muhammad Mahad 21L-6195
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[])
{
    char *name = argv[1];
    int length = 0;
    while(*name != '\0')
    {
        length++;
        name++;
    }
    printf("The length of your name is %d characters.\n", length);
    return 0;

}