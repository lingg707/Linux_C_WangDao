#include"func.h"
//socket、setsockopt、sockaddr_in、bind、listen
int tcpinit(int *sfd,char *ip,char *port)//函数里面若是有返回值，则一定不能携程void
{
    //这里传参为什么一定要把sfd传进来？，初始化实在函数内，函数内产生，只能以返回值的方式传递出函数
    //，因此要重新定义一个参数，并且用指针的方式传参，这样就可以在主函数内定义
    int socketfd;
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketfd,-1,"socket");
    int ret;
    int reuse=1;//这个参数是啥？？
    ret=setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    //创建socket结构体，存储sfd信息，并用bind函数将sfd与信息绑定在一起
    struct sockaddr_in server;
    bzero(&server,sizeof(struct sockaddr_in));
    server.sin_port=htons(atoi(port));
    server.sin_addr.s_addr=inet_addr(ip);
    server.sin_family=AF_INET;

    ret=bind(socketfd,(struct sockaddr*)&server,sizeof(struct sockaddr_in));
    ERROR_CHECK(ret,-1,"bind");

    listen(socketfd,10);

    *sfd=socketfd;//不能写成sfd=&socketfd，要不然不会传递数值
    return 0;
}
