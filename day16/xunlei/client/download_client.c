#include<func.h>
int recvcycle(int sfd,void* pstart,int recvlen)
{
    char *p=(char*)pstart;
    int total=0;
    int ret;
    while(total<recvlen)
    {
        ret=recv(sfd,p+total,recvlen-total,0);
        total=total+ret;
    }
    return 0;
}
int main(int argc,char* argv[])
{
    //socket
    ARGS_CHECK(argc,3);
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    printf("sfd=%d\n",sfd);
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[2]));//这个不会
    server.sin_addr.s_addr=inet_addr(argv[1]);
    //connect函数，与recv直接完成了三次握手
    int ret=connect(sfd,(struct sockaddr*)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"connct");
    int datalen;
    char buf[1000]={0};
    //接收文件名
    recvcycle(sfd,&datalen,4);
    recvcycle(sfd,buf,datalen);
    //接收文件大小
    off_t filesize,downloadsize=0;
    off_t oldsize=0,slicesize;
    recvcycle(sfd,&datalen,4); //这里是recv的话，会出现传输速率不匹配的问题，如果不匹配，则会出现问题
    //下面长度一定要填对，要不然会卡住，而且数据一个都不会传进去
    recvcycle(sfd,&filesize,datalen);//从sfd里面读datalen个字节，存入filesize,datalen可以直接换成8
    printf("filesize :%ld\n",filesize);
    slicesize=filesize/10000;
    int fd;
    fd=open(buf,O_WRONLY|O_CREAT,0666);//文件是现在创建的，文件名为什么默认就是file，自动识别
    
    ERROR_CHECK(fd,-1,"open");
    time_t brefore,now;
    //接文件内容
    brefore=now=time(NULL);
    while(1)
    {
        recvcycle(sfd,&datalen,4);
        if(datalen>0)
        {
            recvcycle(sfd,buf,datalen);
            write(fd,buf,datalen);
            downloadsize+=datalen;
            now=time(NULL);
      //      if(now>brefore)
         //   {
         //       
          //      printf("%5.2f%%\r",(double)downloadsize/filesize*100);
         //       fflush(stdout);
         //       brefore=now;
         //   }
            if(downloadsize-oldsize>=slicesize)
            {
                printf("%5.2f%%\r",(double)downloadsize/filesize*100);
                fflush(stdout);
                oldsize=downloadsize;
            }
        }
        else{
            printf("100%%\n");
            printf("used time:%ld\n",now-brefore);
            break;
        }
    }
    //send(sfd,"hello",5,0);
    //char buf[128]={0};
    //recv(sfd,buf,sizeof(buf),0);//与read相似，龙哥说可以直接用read来实现
    //printf("client reciver ,i got :%s\n",buf);
    close(fd);
    close(sfd);
    return 0;
}
