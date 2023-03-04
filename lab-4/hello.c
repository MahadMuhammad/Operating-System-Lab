/*
    Muhammad Mahad 21L-6195

    This main.c is used in experimetning.c to test the exec()
    family of functions.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    
    // reading from the parematers

    // printing argv to console

    for (int i = 0 ; i < argc ;i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}