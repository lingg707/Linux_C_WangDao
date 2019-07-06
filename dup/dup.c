#include<func.h>
int main()
{
    int fd,fdError;
    fd=open("log1",O_RDWR|O_TRUNC);
    ERROR_CHECK(fd,-1,"open");
    fdError=open("log2",O_RDWR|O_TRUNC);
    ERROR_CHECK(fdError,-1,"open");
    printf("\n");
    int fd1,fdError1;
    fd1=dup2(fd,STDOUT_FILENO);
    fdError1=dup2(fdError,STDERR_FILENO);
    printf("fd1=%d,fdError1=%d\n",fd1,fdError1);
    printf("youcan'tseeme\n");
    perror("function ok");
    return 0;
}
