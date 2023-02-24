/*
    Muhammad Mahad 21L-6195
    count digits in a file
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// count digits in a file
int count_digits(FILE *fp)
{
    char ch;
    int count = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isdigit(ch))
            count++;
    }
    return count;
}

// create & write to file
void check_file_exists(FILE *fp, char const *argv[])
{
    if(fp!=NULL) { return; }

    printf("\nError! File does not exist\n Creating new file!\n");
    fp=fopen(argv[1],"w");

    printf("\nEnter the string: ");

    // take input with spaces
    char temp[100];
    scanf(" %[^\n]s",temp);

    //writing to file
    fprintf(fp,"%s",temp);
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    //printf("\nThe first parameter is the name of the program: %s\n", argv[1]);
    FILE *fp_digit = fopen(argv[1], "r");

    // if file does not exist, create new file
    check_file_exists(fp_digit, argv);

    // Again reopening becuase function didn't point main pointer to the file
    fp_digit = fopen(argv[1], "r");
    printf("\nTotal digits in the file = %d\n", count_digits(fp_digit));

    fclose(fp_digit);
    return 0;
}
    