/*
a. Create a file named main.c and write a code to print “Welcome to BSBS Operating
System Lab Course” on terminal.
b. main.c file contains the main function receiving command-line arguments.
c. You will pass the name of Course via these arguments.
*/
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    printf("Welcome to BSBS Operating System Lab %s", argv[1]);
    printf("\n");
    return 0;
}