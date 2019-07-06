#include<func.h>

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
    send(sfd,"hello",5,0);
    char buf[128]={0};
    recv(sfd,buf,sizeof(buf),0);//与read相似，龙哥说可以直接用read来实现
    printf("client reciver ,i got :%s\n",buf);
    close(sfd);
    return 0;
}
