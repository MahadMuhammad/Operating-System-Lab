/*
    Write a program that reverses all the characters of words that are not vowels in a given
    file.
    Abcd->Adcb
    Vowel->Lowev
    Operating->Ogenatirp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void SWAP(char *a,char *b)
{
    char temp=*a;
    *a=*b;
    *b=temp;
}
bool is_vowel(char c)
{
    c=tolower(c);
    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
        return true;
    else
        return false;
}

void reverse_character(char *str)
{
    unsigned int start=0;
    unsigned int end=strlen(str)-1;

    while(start<end)
    {
        if(is_vowel(str[start]))
            start++;
        else if(is_vowel(str[end]))
            end--;
        else
        {
            SWAP(&str[start],&str[end]);
            start++;
            end--;
        }
    }
}

int main(int argc,char *argv[])
{
    FILE *f_reverse=fopen(argv[1],"r");;
    char str[100];

    // total words in the file
    int count=0;
    while(fscanf(f_reverse,"%s",str)!=EOF)
    {
        count++;
    }
    printf("\nTotal words in the file = %d ",count);

    
    // reverse the characters of words that are not vowels
    rewind(f_reverse);
    while(fscanf(f_reverse,"%s",str)!=EOF)
    {
        reverse_character(str);
        printf("%s ",str);
    }
    fclose(f_reverse);
    
    f_reverse=fopen(argv[1],"w");
    fprintf(f_reverse,"%s",str);


    return 0;
}


