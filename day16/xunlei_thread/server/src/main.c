#include "factory.h"

int main(int argc,char *argv[])
{
    if(argc!=5)
    {
        printf("./server ip port threadnum capacity");
        return -1;
    }
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
    while(1)
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
    return 0;
}
