#include<func.h>
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd;
    sfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[2]));
    server.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=bind(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr));//不拆开报错。。
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    char buf[128]={0};
    recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
    printf("gets:%s\n",buf);
    printf("client ip:%s,client port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    sendto(sfd,"world",5,0,(struct sockaddr*)&client,sizeof(client));
    close(sfd);
    return 0;
}
