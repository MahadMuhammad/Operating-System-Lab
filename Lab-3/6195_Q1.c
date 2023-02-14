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
		printf("%d ",arr[i]);
}

void my_swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int main(int argc,char *argv[])
{
	//checking if user enter 10 arguments
	if(argc!=11)
	{
		printf("\nPlease Enter correct arguments\nTerminating...\n");
		exit(0);
	}

	int arr[10];
	input_array(arr,argv);

	printf("\nThe input array is: ");
	print_array(arr);


	//creating child process to sort array in ascending order 
	pid_t pid=fork();

	if(pid == 0)
	{
		printf("\nI am child process\nI am here to sort the array for you :) \n");
		int min_index;

		for(int i=0;i<10;i++)
		{
			//assuming ith index has the smallest number
			min_index=i;

			for(int j=i+1;j<10;j++)
			{
				//checking our assumption
				if(arr[min_index]>arr[j])
					min_index=j;
			}
			my_swap(&arr[min_index],&arr[i]);
		}

		printf("\nSorted Array is: ");
		print_array(arr);
		printf("\nI am child process & my id is %d\n",getpid());
		exit(0);
	}



	return 0;
}