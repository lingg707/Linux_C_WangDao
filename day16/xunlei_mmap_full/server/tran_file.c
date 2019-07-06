#include "process_pool.h"
//1、文件名。2、文件内容。3、结束符
int tranfile(int newfd)
{
    train_t t;
    t.datalen=strlen(FILENAME);
    strcpy(t.buf,FILENAME);//先放文件名//控制码一般要转成大端，对端收到之后呀转为小段
    send(newfd,&t,4+t.datalen,0);//发送文件名,t就相当于buf//传文件名，传内容需要一个循环,为啥取地址不能取buf的地址
    printf("%c %c %c %c %c %c %c %c \n",t.buf[0],t.buf[1],t.buf[2],t.buf[3],t.buf[4],t.buf[5],t.buf[6],t.buf[7]);
printf("%d\n",t.datalen);
    int fd=open(FILENAME,O_RDONLY);//打开文件进行读，然后发送
    ERROR_CHECK(fd,-1,"open");
    //发送文件大小
    struct stat buf;//存储文件信息的结构体
    fstat(fd,&buf);//把fd的文件信息传递到buf里
    t.datalen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,t.datalen);//只能用memcpy，禁止用strcpy
    send(newfd,&t,4+t.datalen,0);

    struct timeval start,end;
    gettimeofday(&start,NULL);
    char *pmap=(char*)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    send(newfd,pmap,buf.st_size,0);
    //while((t.datalen=read(fd,t.buf,sizeof(t.buf))))//文件读空，返回0，此判断，先赋值再判断
    // send(newfd,&t,4+t.datalen,0);//发送最后的一个残留的包
    gettimeofday(&end,NULL);
    printf("send used time:%ldum\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    return 0;
}
