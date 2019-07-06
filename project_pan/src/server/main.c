#include "factory.h"
#include "func.h"
#include"workque.h"
int main(int argc,char* argv[])
{
    if(argc!=5)
    {
        printf("server_ip,port,threadnum,max(capacity)\n");
        return -1;
    }
    factory mainthread;
    int threadnum=atoi(argv[3]);
    int max=atoi(argv[4]);
    factoryinit(&mainthread,threadnum,max);
    printf("factoryinit success\n");
    factorystart(&mainthread);

    int sfd;    
    tcpinit(&sfd,argv[1],argv[2]);
    int newfd;
    
    pnode pnew;//线程池外部定义，内部申请空间，为啥？？？
    pque pq=&mainthread.queue;
    queinit(pq,max);
    while(1)
    {
        pnew=(struct que_node*)calloc(1,sizeof(struct que_node));
        newfd=accept(sfd,NULL,NULL);
        pthread_mutex_lock(&pq->mutex);
        pnew->newfd=newfd;//这一步和老师写的位置不一样，但是我觉得可以。试一下
        queinsert(pq,pnew);
        pthread_mutex_unlock(&pq->mutex);
        pthread_cond_signal(&mainthread.cond);

    }
    return 0;
}
