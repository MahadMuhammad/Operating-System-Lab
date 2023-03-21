#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd=open("T3", O_RDWR);
	
	char operator;
	float operand1, operand2;
	
	read(fd, &operator, sizeof(char));
	read(fd, &operand1, sizeof(float));
	read(fd, &operand2, sizeof(float));
	
	float result;
	if(operator=='+')
		result=operand1+operand2;
	else if(operator=='-')
		result=operand1-operand2;
	else if(operator=='*')
		result=operand1*operand2;
	else if(operator=='/')
		result=operand1/operand2;
		
	write(fd, &result, sizeof(float));		
	
	return 0;
}
