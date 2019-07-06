#include "factory.h"
int exitfds[2];
//进程退出函数sigexitfunc和epolladd
void sigexitfunc(int signum)
{
    printf("%d sig is coming\n",signum);
    write(exitfds[1],&signum,1);
}
int epolladd(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

int main(int argc,char *argv[])
{
    if(argc!=5)
    {
        printf("./server ip port threadnum capacity");
        return -1;
    }
    pipe(exitfds);
    if(fork())//父进程.信号在父进程 内注册
    {
        close(exitfds[0]);//关闭读
        signal(SIGUSR1,sigexitfunc);
        wait(NULL);//父进程等待子进程的退出
        printf("exit success\n");
        exit(0);
    }
    close(exitfds[1]);

    factory threadmaindata;
    int threadnum=atoi(argv[3]);//最大并发数
    int capacity=atoi(argv[4]);//最大能服务的客户端数
    factoryinit(&threadmaindata,threadnum,capacity);//初始化队列，初始化条件变量
    //factorystart里面包含threadfunc
    factorystart(&threadmaindata);//线程数未达标，就接着创建新的线程，就是创建线程的工厂
    printf("thread create done,sum of thread is:%d\n",threadmaindata.threadnum);
    int sfd,newfd;
    tcpinit(&sfd,argv[1],argv[2]);//sfd,bind,listen
    printf("tcpinit success\n");
    pque pq=&threadmaindata.que;//头尾，长度，capacity，互斥锁，队列结构体
    pnode pnew;//队列节点的结构体，与上一条组成一个队列，内容newfd，next指针
    int epfd=epoll_create(1);//这里课件写错了，epoll不限制监控的描述符数量，参数填1就行
    //监控读端和sfd
    struct epoll_event evs[2];
    epolladd(epfd,sfd);
    epolladd(epfd,exitfds[0]);
    int count,i,j; 
    while(1)//子进程
    {   
        count=epoll_wait(epfd,evs,2,-1);//进程池信号会造成epollwait失败
        for(i=0;i<count;i++)
        {
            if(evs[i].data.fd==sfd)
            {
                newfd=accept(sfd,NULL,NULL);
                pnew=(pnode)calloc(1,sizeof(node));
                pnew->newfd=newfd;
                pthread_mutex_lock(&pq->mutex);
                queinsert(pq,pnew);
                printf("queinsert success\n");
                pthread_mutex_unlock(&pq->mutex);
                pthread_cond_signal(&threadmaindata.cond);
                printf("cond signal success\n");
            }
            if(evs[i].data.fd==exitfds[0])
            {
                //给每个子线程发cancel信号
                for(j=0;j<threadnum;j++)//循环cancel，之后循环join，两个一定要搭配
                {
                    pthread_cancel(threadmaindata.pthid[j]);
                }
                for(j=0;j<threadnum;j++)
                {
                    pthread_join(threadmaindata.pthid[j],NULL);
                }
                exit(0);
            }
        }
        return 0;
    }
}
