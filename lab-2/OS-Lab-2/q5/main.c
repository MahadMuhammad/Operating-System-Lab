/*
In main.c you will accept command line arguments including 3 things
•
•
•
an array of integers
order of sort (1 for ascending order and 0 for descending order)
nth position to get the nth highest number from the array
Use makefile to execute all these files. Your makefile will look like
*/

#include "header.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{    
    int i;
    int array[10];
    bool order=true;
    int position=1;
    for(i=0;i<10;i++)
    {
        array[i]=atoi(argv[i+1]);
    }
    sort(array,order);
    print(array);
    findHighest(array,position);

    return 0;
}