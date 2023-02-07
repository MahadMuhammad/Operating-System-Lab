//functions.c file contains following 3 functions along with their logic

#include <stdio.h>
#include <stdlib.h>

void sort(int array[],bool order)
{
    //if order is true sort in ascending order
    //if order is false sort in descending order
    int temp;
    for(int i=0;i<argc-1;i++)
    {
        for(int j=i+1;j<10;j++)
        {
            if(order)
            {
                if(array[i]>array[j])
                {
                    temp=array[i];
                    array[i]=array[j];
                    array[j]=temp;
                }
            }
            else
            {
                if(array[i]<array[j])
                {
                    temp=array[i];
                    array[i]=array[j];
                    array[j]=temp;
                }
            }
        }
    }
}