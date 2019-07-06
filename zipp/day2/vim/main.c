#include <stdio.h>

int main()
{
	printf("helloworld\n");
	FILE* fp;
	fp=fopen("noexist","rb+");
	if(NULL==fp)
	{
		perror("fopen");
	}    
	return 0;
}

