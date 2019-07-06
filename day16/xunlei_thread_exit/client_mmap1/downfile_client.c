#include<func.h>

int recvCycle(int sfd,void* pStart,int recvLen)
{
    printf("start recvcycle\n");
    char *p=(char*)pStart;
    int total=0;
    int ret;
    while(total<recvLen)
    {
        ret=recv(sfd,p+total,recvLen-total,0);
        total=total+ret;
        printf("%5.2f%%\r",(double)total/recvLen*100);
        fflush(stdout);
    }
    printf("\n");
    return 0;                                          
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    //server的套接字初始化
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    int dataLen;
    int e;
    char buf[1000]={0};
    recv(socketFd,&dataLen,4,MSG_WAITALL);
    e=recv(socketFd,buf,dataLen,MSG_WAITALL);
    if(e<=0)
    {
        perror("recv");
        return -1;
    }
    off_t fileSize=0;
    recv(socketFd,&dataLen,4,MSG_WAITALL);//标志位表示所有要求都满足的情况下才执行函数
    e=recv(socketFd,&fileSize,dataLen,MSG_WAITALL);
    if(e<=0)
    {
        perror("recv");
        return -1;
    }
    printf("fileSize=%ld\n",fileSize);
    int fd;
    fd=open(buf,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    e=ftruncate(fd,fileSize);
    if(e!=0)
    {
        perror("ftruncate");
        return -1;
    }
    char *pMap=(char*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pMap,(char*)-1,"mmap");
    recvCycle(socketFd,pMap,fileSize);
    ret=munmap(pMap,fileSize);
    ERROR_CHECK(ret,-1,"munmap");
    close(fd);
    close(socketFd);
}

