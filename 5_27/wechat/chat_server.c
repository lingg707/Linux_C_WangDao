#include<func.h>
int tcpinit(int *sFd,char* ip,char* port)
{
    //socket生成一个套接口描述符
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    printf("socket num of server is:%d\n",sfd);
    //bind绑定一个端口号和IP地址
    struct sockaddr_in server;
    bzero(&server,sizeof(server));//memset(&server,0,sizeof(server))
    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(port));//括号内表示端口号
    server.sin_addr.s_addr=inet_addr(ip);//括号内表示ip地址
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
    *sFd=sfd;
    return 0;
}
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int sfd;
    tcpinit(&sfd,argv[1],argv[2]);//初始化完成服务器端
    //开始初始化客户端
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t addrlen=sizeof(struct sockaddr_in);//addrlen的类型修改了
    int newfd=accept(sfd,(struct sockaddr*)&client,&addrlen);//全双工的端口
    ERROR_CHECK(newfd,-1,"accept");
    printf("client ip is:%s,client port is:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    //recive函数，用心的套接字来接收远端主机发来的数据，并把数据存到由参数buf指向的内存空间
    char buf[512]={0};
    //select函数
    fd_set rdset;
    int count;
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(newfd,&rdset);
        count=select(newfd+1,&rdset,NULL,NULL,NULL);
        if(count>0)//select函数判断，返回值为正表示可读
        {
            if(FD_ISSET(newfd,&rdset))//newfd可读
            {
                memset(buf,0,sizeof(buf));
                ret=recv(newfd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("see you \n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))//标准输入流可读
            {
                bzero(buf,sizeof(buf));
                //memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                send(newfd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(newfd);
    close(sfd);
    return 0;
}
