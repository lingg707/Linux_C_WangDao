#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT,0766);
    ERROR_CHECK(fd,-1,"open");
    char buf[6]="hello";
    lseek(fd,-5,SEEK_END);
    write(fd,buf,5);
    return 0;
}
