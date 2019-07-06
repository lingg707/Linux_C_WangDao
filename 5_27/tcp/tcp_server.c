#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    //socket生成一个套接口描述符
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    printf("socket num of server is:%d\n",sfd);
    //bind绑定一个端口号和IP地址
    struct sockaddr_in server;
    bzero(&server,sizeof(server));//memset(&server,0,sizeof(server))
    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[2]));//括号内表示端口号
    server.sin_addr.s_addr=inet_addr(argv[1]);//括号内表示ip地址
    int ret;
    ret=bind(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    //listen使服务器的端口和ip处于监听状态
    if(listen(sfd,10)==-1)
    {
        perror("listen");
        close(sfd);
        exit(-1);
    }
    //accept函数，接受远程计算机的连接请求，先将请求放到等待队列里
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    int addrlen=sizeof(struct sockaddr_in);
    int newfd=accept(sfd,(struct sockaddr*)&client,&addrlen);
    ERROR_CHECK(newfd,-1,"accept");
    printf("client ip is %s,client port is%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    //recive函数，用心的套接字来接收远端主机发来的数据，并把数据存到由参数buf指向的内存空间
    char buf[512]={0};
    if(recv(newfd,buf,sizeof(buf),0)==-1)
    {
        perror("recv");
        close(newfd);
        close(sfd);
        exit(-1);
    }
    printf("server recv port,i resive %s\n",buf);
    send(newfd,"world",5,0);
    close(newfd);
    close(sfd);
    return 0;
}
