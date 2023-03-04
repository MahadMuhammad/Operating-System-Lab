/*
    Muhammad Mahad 21L-6195
*/
#include <stdio.h>
#include <stdlib.h>

// creating inline swap function
// inline void swap(int *a, int *b)
// {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

int main(int argc, char const *argv[])
{
    int fib = atoi(argv[1]);

    int a = 0, b = 1, c = 0;

    for (int i = 0; i < fib; i++)
    {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }



    return 0;
}