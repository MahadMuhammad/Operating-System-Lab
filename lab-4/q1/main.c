/*
    Muhammad Mahad 21L-6195

    Task-1 : execv() 

        Write a C program called main.c and replace it using execv with another program
        named my_info.c. 

        The second process should print the name, roll number, and your semester number.
        Explain verbally to the instructor the working of the function of execv. 

        Print process ID before calling execv in main.c

        Also print process ID in my_info.c before printing your own information.
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    /* Execute PATH with arguments ARGV and environment 
    from `environ'.  */

    printf("\nProcess ID of main.c: %d\n", getpid());
    printf("Calling my_info.c from main.c\n\n");

    // int execv(executable file, arguments)
    
    char *argv[] = {"./my_info.out",NULL};
    execv(argv[0],argv);

    printf("Error! Couldn't replace main.c with my_info.c\n");

    
    return 0;

}