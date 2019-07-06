#include <func.h>
int tcpinit(int *sfd,char* ip,char* port)
{
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    *sfd=socketFd;
    return 0;
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd,newfd;
    tcpinit(&sfd,argv[1],argv[2]);//初始化完成服务器端
    //开始初始化客户端
    struct sockaddr_in client;
    //bzero(&client,sizeof(client));//这两条的修改，因为client结构体要重复使用，因此要定义的到while循环中
    //socklen_t addrlen=sizeof(struct sockaddr_in);//addrlen的类型修改了
    printf("client ip is:%s,client port is:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    //recive函数，用心的套接字来接收远端主机发来的数据，并把数据存到由参数buf指向的内存空间
    char buf[128]={0};
    //select函数
    fd_set rdset,monitor;//这是结构体
    int count;
    int ret;
    FD_SET(STDIN_FILENO,&monitor);//监控1
    FD_SET(sfd,&monitor);//监控这两个描述符
    while(1)
    {
        FD_ZERO(&rdset);
        memcpy(&rdset,&monitor,sizeof(fd_set));//把要监控的描述符传入while（1），但是不修改 monitor的值
        //FD_SET(STDIN_FILENO,&rdset);
        //FD_SET(newfd,&rdset);//以上原来监视的两个描述符被放在循环外
        count=select(15,&rdset,NULL,NULL,NULL);//第一个参数原来是newfd+1，现在表示最大监控的值由15个
        if(count>0)//select函数判断，返回值为正表示可读
        {//以下每个if判断，都是判断监控的描述符中是否有数据
            if(FD_ISSET(sfd,&rdset))//newfd改成sfd，why？？？
            {
                bzero(&client,sizeof(client));                                    
                socklen_t addrlen=sizeof(struct sockaddr_in);//addrlen的类型修改了
                newfd=accept(sfd,(struct sockaddr*)&client,&addrlen);
                printf("client ip:%s,client port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                FD_SET(newfd,&monitor);//新建链接，添加到监控        
                //原来的if recv返回值为0，break，取消了
            }
            if(FD_ISSET(newfd,&rdset))
            {
                bzero(buf,sizeof(buf));
                //memset(buf,0,sizeof(buf));
                //read(STDIN_FILENO,buf,sizeof(buf)-1);
                //send(newfd,buf,strlen(buf)-1,0);
                ret=recv(newfd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("connection break down\n");
                    close(newfd);
                    FD_CLR(newfd,&monitor);
                }
                else{
                    printf("%s\n",buf);
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);//减一是因为不想读入换行符
                if(ret==0)
                {
                    printf("connection break down\n");
                    break;
                }
                send(newfd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(sfd);
    return 0;
}
