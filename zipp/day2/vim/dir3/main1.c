#include <stdio.h>

int main()
{
    printf("helloworld\n");
    FILE* fp;
    fp=fopen("noexist","rb+");
    int i,j;
    i^j;
    if(NULL==fp)
    {
        perror("fopen");
    }
    return 0;
}

