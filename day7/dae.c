#include<func.h>

int main()
{
    int i=0;
    if(fork()!=0)
    {
        exit(0);
    }
    setsid();
    chdir("/");
    umask(0);
    for(i=0;i<64;i++)
    {
        close(i);
    }
    int fd=open("/tmp/log",O_RDWR);
    char buf[11];
    strcpy(buf,"caideyibi\n");
    while(1)
    {
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    return 0;
}
