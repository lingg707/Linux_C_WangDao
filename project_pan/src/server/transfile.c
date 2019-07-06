#include "factory.h"

int transfile(int newFd)
{
    train t;
    t.datalen=strlen(FILENAME);//要转为网络字节序，对端接收到以后，要转主机字节序
    strcpy(t.buf,FILENAME);
    send(newFd,&t,4+t.datalen,0);//发送文件名
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    //发文件大小
    struct stat buf;
    fstat(fd,&buf);
    t.datalen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,t.datalen);
    send(newFd,&t,4+t.datalen,0);
    struct timeval start,end;
    gettimeofday(&start,NULL);
    char *pMap=(char*)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    send(newFd,pMap,buf.st_size,0);
    //    send(newFd,&t,4+t.dataLen,0);//告诉客户端文件发送结束
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    return 0;

}
