#include"process_pool.h"
int epolladd(int epfd,int fd)//函数的目的是把fd加入监听
{
    struct epoll_event event;//这个结构体告诉内核需要做的事情
    event.events=EPOLLIN;//对应的文件描述符可读
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);//注册新的fd到epfd中，参数三表示需要监听的fd，参数四，告诉内核需要做的事，是一个结构体
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}
int main(int argc,char* argv[])//ip，port，子进程数，传三个参数
{
    ARGS_CHECK(argc,4);
    //创建进程池，即子进程
    int processnum=atoi(argv[3]);
    pProcessData_t pmaindata=(pProcessData_t)calloc(processnum,sizeof(ProcessData_t));
    makechild(pmaindata,processnum);
    for(int i=0;i<processnum;i++)
    {
        printf("%d\n",pmaindata[i].fds);
    }
    //分割线
    int sfd;
    int ret;
    ret=tcpinit(&sfd,argv[1],argv[2]);
    ERROR_CHECK(ret,-1,"tcpinit");
    //初始化tcp服务器完成
    int epfd=epoll_create(1);//参数表示监听的数目
    struct epoll_event *evs;//告诉内核要做的事情的结构体
    evs=(struct epoll_event*)calloc(processnum+1,sizeof(struct epoll_event));//分配evs结构体空间
    epolladd(epfd,sfd);
    int i;
    for(i=0;i<processnum;i++)
    {
        epolladd(epfd,pmaindata[i].fds);
    }
    //分割线查找非忙碌子进程，监听子进程的管道
    int count,newfd,j;
    char flag;
    while(1)
    {
        count=epoll_wait(epfd,evs,processnum+1,-1);//最后的-1表示超时时间，永久阻塞
        for(i=0;i<count;i++)
        {
            if(evs[i].data.fd==sfd)
            {
                newfd=accept(sfd,NULL,NULL);//不想知道客户端的ip和port，就填NULL，NULL,仅仅是不从内核中拿出来
                //找非忙碌的子进程
                for(j=0;j<processnum;j++)
                {
                    if(!pmaindata[j].busy)
                    {
                        //write(pmaindata[j].fds,&newfd,sizeof(int));//把描述符newfd给子进程的fds
                        sendfd(pmaindata[j].fds,newfd);
                        pmaindata[j].busy=1;
                        printf("the child with pid:%d is busy\n",pmaindata[j].pid);
                        break;
                    }
                }
                close(newfd);
            }
            for(j=0;j<processnum;j++)//先读取，再标记为非忙碌，遍历全部的子进程
            {
                if(evs[i].data.fd==pmaindata[j].fds)
                {
                    read(pmaindata[j].fds,&flag,1);//读到flag里面
                    printf("work done\n");
                    printf("child with pid:%d id not busy\n",pmaindata[j].pid);
                    pmaindata[j].busy=0;
                    break;
                }
            }
        }
    }
    return 0;
}
