#include "process_pool.h"

int makechild(pProcessData_t p,int processnum)
{
    int i;
    pid_t pid;
    int fds[2];//创建管道,用于父进程与子进程的通信
    int ret;
   for(i=0;i<processnum;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//做管道的函数，创建本地的socket
        //内核控制信息必须由此函数控制，全双工，一个描述符，该函数传递内核控制信息的时候十分稳定，一直就是这几个参数
        ERROR_CHECK(ret,-1,"socketpair");//create a pair of connected sockets
        pid=fork();//fork也复制了父进程的fds管道
        if(pid==0)
        {
            close(fds[1]);//各自关闭一端，管道，子进程
            childhandle(fds[0]);//子进程不退出
        }
        //fork之后，复制了fds，因此需要关闭，要不然一个进程由两个读端两个写端，一对就可以完成全双工
        close(fds[0]);//父进程关闭读
        p[i].pid=pid;
        p[i].fds=fds[1];//这个fds每次循环都不同,用于写，子进程的。为啥不是fds0？？
        p[i].busy=0;
    }
   return 0;
}

int childhandle(int pipefd)
{
    int newfd;//这全双工端口是为了干嘛？
    while(1)
    {
        recvfd(pipefd,&newfd);//此时newfd是子进程中未使用的文件描述符的最小编号
       // read(pipefd,&newfd,sizeof(int));//从端口读一个整形到newfd，接受任务
        printf("child i am,rager task%d\n",newfd);
        send(newfd,"file",4,0);//模拟发文件，实际file只是字符串
        close(newfd);
        write(pipefd,&newfd,1);//通知父进程非忙碌，newfd写入pipefd
    }
}
