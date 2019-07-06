#include<func.h>

int main(int argc,char* argv[])
{
    int fdr,fdw,ret;
    fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    fdr=open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("chat2 this is,fdr=%d,fdw=%d\n",fdr,fdw);
    char buf[128]={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int ret=read(fdr,buf,sizeof(buf));//这里会阻塞
        printf("%s\n",buf);

        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf)-1);
        write(fdw,buf,strlen(buf)-1);//因为read读取，最后又/n，不想发/n，就要减一
    }
    return 0;
}

