#include "process_pool.h"
//1、文件名。2、文件内容。3、结束符
int tranfile(int newfd)
{
    train_t t;
    t.datalen=strlen(FILENAME);
    strcpy(t.buf,FILENAME);//先放文件名//控制码一般要转成大端，对端收到之后呀转为小段
    send(newfd,&t,4+t.datalen,0);//发送文件名,t就相当于buf//传文件名，传内容需要一个循环
    int fd=open(FILENAME,O_RDONLY);//打开文件进行读，然后发送
    ERROR_CHECK(fd,-1,"open");
    //发送文件大小
    struct stat buf;//存储文件信息的结构体
    fstat(fd,&buf);//把fd的文件信息传递到buf里
    t.datalen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,t.datalen);//只能用memcpy，禁止用strcpy
    send(newfd,&t,4+t.datalen,0);
    int ret;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    char *pmap=(char*)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    //while((t.datalen=read(fd,t.buf,sizeof(t.buf))))//文件读空，返回0，此判断，先赋值再判断
    off_t pos=0;//设置偏移量
    while(buf.st_size-pos>=1000)//判断条件，剩下一个零头的时候退出
    {
        t.datalen=1000;
        memcpy(t.buf,pmap+pos,1000);
        ret=send(newfd,&t,4+t.datalen,0);//每次都发送文件长度加上一个int型，就是4，因为结构体为int datalen
        if(-1==ret)//如果不判断-1，那么客户端断开，服务器会崩溃
        {
            goto end;
        }       
        pos=pos+1000;//设置指针偏移
    }
    t.datalen=buf.st_size-pos;
    memcpy(t.buf,pmap+pos,t.datalen);
    send(newfd,&t,4+t.datalen,0);//发送最后的一个残留的包
    t.datalen=0;
    send(newfd,&t,4,0);//最后一次发送，read返回0，判断失败，运行这一行，告诉主进程发送完毕
    gettimeofday(&end,NULL);
    printf("send used time:%ldum\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
end:
    close(fd);
    return 0;
}
