//Write a program that takes multiple numbers from the user through command line arguments.
// Print the sum and average of these numbers on the terminal.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, sum = 0;
    int average;
    for (i = 1; i < argc; i++)
    {
        sum += atoi(argv[i]);
    }
    average = sum / (argc - 1);
    printf("Sum of the numbers is %d and average is %d", sum, average);
    printf("\n");

    return 0;
}