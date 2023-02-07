
#include "header.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void myswap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void sort(int array[],bool order)
{
    int i,j,temp;
    if(order==true)
    {
        for(i=0;i<10;i++)
        {
            for(j=i+1;j<10;j++)
            {
                if(array[i]>array[j])
                {
                    myswap(&array[i],&array[j]);
                }
            }
        }
    }
    else
    {
        for(i=0;i<10;i++)
        {
            for(j=i+1;j<10;j++)
            {
                if(array[i]<array[j])
                {
                    myswap(&array[i],&array[j]);
                }
            }
        }
    }
}

void findHighest(int array[],int position)
{
    // if position is 1 then find first highest number
    // if position is 2 then find second highest number

    int i,j,temp;
    for(i=0;i<position;i++)
    {
        for(j=i+1;j<10;j++)
        {
            if(array[i]<array[j])
            {
                myswap(&array[i],&array[j]);
            }
        }
    }
    printf("\n %d highest number is %d \t",position,array[position-1]);
    printf("\n");
}

void print(int array[])
{
    for(int i=0;i<10;i++)
    {
        printf("%d  ",array[i]);
    }
}
