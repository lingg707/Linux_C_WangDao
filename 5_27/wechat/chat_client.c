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
    char buf[128]={0};
    //select函数
    fd_set rdset;
    int count;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sfd,&rdset);
        count=select(sfd+1,&rdset,NULL,NULL,NULL);
        if(count>0)
        {
            if(FD_ISSET(sfd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(sfd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("disconnet\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                send(sfd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(sfd);
    return 0;
}
