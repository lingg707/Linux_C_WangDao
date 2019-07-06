#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fp=open(argv[1],O_RDWR);
    ERROR_CHECK(fp,-1,"open");
    char *p;
    int ret;
    struct stat buf;
    ret=stat(argv[1],&buf);
    p=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fp,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    write(fp,"world",5);
    int ret1=munmap(p,buf.st_size);
    ERROR_CHECK(ret1,-1,"munmap");
    return 0;
}
