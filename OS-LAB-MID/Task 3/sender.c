#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd=open("T3", O_RDWR);
	
	char operator;
	float operand1, operand2;
	
	operator=argv[1][0];
	operand1=atoi(argv[2]);
	operand2=atoi(argv[3]);
	
	//printf("Enter the operator: ");
	//scanf("%c", &operator);
	//printf("Enter the operands: ");
	//scanf("%f %f", &operand1, &operand2);
	
	write(fd, &operator, sizeof(char));
	write(fd, &operand1, sizeof(float));
	write(fd, &operand2, sizeof(float));
	
	sleep(2);
	
	float result;
	
	read(fd, &result, sizeof(float));
	
	printf("The result of %f %c %f is: %f", operand1, operator, operand2, result);
	
	return 0; 
}
