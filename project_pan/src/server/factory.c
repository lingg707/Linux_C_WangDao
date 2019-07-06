#include"factory.h"
#include"func.h"
#include"workque.h"
int factoryinit(pfactory pf,int threadnum,int max)//该函数完全按照factory结构体初始化
{
    queinit(&pf->queue,max);
    pthread_cond_init(&pf->cond,NULL);
    pf->flag=0;
    pf->pthid=(pthread_t*)calloc(threadnum,sizeof(pthread_t));
    pf->threadnum=threadnum;
    return 0;
}
//子线程函数
void *threadfunc(void* p)
{
    int ret=0;
    pfactory pf=(pfactory)p;
    //老师多定义一个pq
    pnode pcur;//要从队列中拿newfd的节点,这里是二级指针的方式，目前还不知道为啥  
    while(1)
    {
        pthread_mutex_lock(&pf->queue.mutex);
        if(pf->queue.tail==NULL)
        {
            pthread_cond_wait(&pf->cond,&pf->queue.mutex);
        }
        queget(&pf->queue,&pcur);
        pthread_mutex_unlock(&pf->queue.mutex);
        while(1){
            char buf[8]={0};
            recv(pcur->newfd,buf,7,0);//服务器收到了命令
            //子线程开始判断，命令
            if(ret!=-1){
                printf("命令接受成功:%s\n",buf);
            }
            if(strncmp(buf,(char*)"ls",2)==0)
            {
                com_ls(pcur->newfd);
            }
            else if(strncmp(buf,(char*)"cd",2)==0)
            {
                com_cd();
            }
            else if(strncmp(buf,(char*)"put",3)==0)
            {
                com_put();
            }
            else if(strncmp(buf,(char*)"get",3)==0)
            {
                com_get();
            }
            else if(strncmp(buf,(char*)"help",4)==0)
            {
                com_help();
            }
            else if(strncmp(buf,(char*)"exit",4)==0)
            {
                com_exit();
                break;
            }

            else
                printf("command error! Try Again\n");
            //continue;
        }
        free(pcur);
        pcur=NULL;
    }
}
int factorystart(pfactory pf)
{
    int i=0;
    if(pf->flag==0)
    {
        for(i=0;i<pf->threadnum;i++)
        {
            pthread_create(pf->pthid+i,NULL,threadfunc,pf);
        }
        pf->flag=1;
    }
    return 0;
}
