#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void input_array(int arr[],char *argv[])
{
    for(int i=0;i<10;i++)
        arr[i]=atoi(argv[i+1]);
}

void print_array(int arr[])
{
    for(int i=0;i<10;i++)
        printf(" %d ",arr[i]);
}

void my_swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int main(int argc,char *argv[])
{
    //checking user entered correct input
    if(argc!=11)
    {
        printf("\nPlear Enter correct arguments\nTerminating...\n");
        exit(0);
    }

    int arr[10]={0};
    input_array(arr,argv);
    // printf("\nThe input array is : ");
    // print_array(arr);

    // creating two child process
    // one for sorting in ascending order
    // other for sorting in descending order
    pid_t child_1=fork();
    pid_t child_2=fork();


    if(child_1 > 0 && child_2 > 0) //parent process
    {
    	wait(NULL);
        wait(NULL);
        printf("\nParent Process terminating and my ID = %d and parent's ID = %d\n\n",getpid(),getppid());
    }
    else if(child_1 == 0 && child_2 != 0)   // child 1 process
    {

        for(int i=0;i<10;i++)
        {
            int f_min_index=i;
            for(int j=i+1;j<10;j++)
                if(arr[f_min_index]>arr[j])
                    f_min_index=j;
            my_swap(&arr[f_min_index],&arr[i]);
        }
        printf("\nI am Child 1 (with ID = %d and Parent's ID = %d): ",getpid(),getppid());
        print_array(arr);
        exit(0);
    }
    else if( child_2 == 0 && child_1 !=0)   // child 2 process
    {
        for(int i=0;i<10;i++)
        {
            int f_max_index=i;
            for(int j=i+1;j<10;j++)
                if(arr[f_max_index]<arr[j])
                    f_max_index=j;
            my_swap(&arr[f_max_index],&arr[i]);
        }
        printf("\nI am Child 2 (with ID = %d and Parent's ID = %d): ",getpid(),getppid());
        print_array(arr);
        exit(0);
    }
    return 0;
}
