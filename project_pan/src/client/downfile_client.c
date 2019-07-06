#include"func.h"

int recvcycle(int sfd,void* pstart,int recvlen)
{
    printf("start recvcycle\n");
    char *p=(char*)pstart;
    int total=0;
    int ret;
    while(total<recvlen)
    {
        ret=recv(sfd,p+total,recvlen-total,0);
        total=total+ret;
        printf("%5.2f%%\r",(double)total/recvlen*100);
        fflush(stdout);
    }
    printf("\n");
    return 0;                                          
}
int tcpinit_c(int *sfd,char* ip,char *port)
{
    int socketfd;
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketfd,-1,"socket");
    printf("socketfd=%d\n",socketfd);
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    //server的套接字初始化
    client.sin_family=AF_INET;
    client.sin_port=htons(atoi(port));
    client.sin_addr.s_addr=inet_addr(ip);
    int ret;
    ret=connect(socketfd,(struct sockaddr*)&client,sizeof(client));
    ERROR_CHECK(ret,-1,"connect");
    *sfd=socketfd;
    printf("connect to server successfully\n");
    return 0;
}

