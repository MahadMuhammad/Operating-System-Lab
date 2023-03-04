/* 
    Muhammad Mahad 21L-6195

    Used in q1/main.c

*/
#include <stdio.h> /* for printf and scanf*/
#include <unistd.h> /* for getpid() */

int main()
{
    
    printf("--- We are in my_info.c ---\n");
    printf("\nProcess ID of my_info.c: %d\n", getpid());
    printf("Name: Muhammad Mahad\n");
    printf("Roll No: 21L-6195\n");
    printf("Section: A\n");

    return 0;
}