#include <stdio.h>
#include <sys/stat.h>

int main()
{
	if(mkfifo("T3", 0777) == -1)
		printf("Could not create pipe\n");
	
	printf("The sender program accepts arguments from the console. In case of multiplication, enclose * in quotation marks as '*' before entering\n");
	
	return 0;
}
