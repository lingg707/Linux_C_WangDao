#include "factory.h"

int factoryinit(pfactory pf,int threadnum,int capacity)
{
    queinit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
    pf->pthid=(pthread_t*)calloc(threadnum,sizeof(pthread_t));
    pf->threadnum=threadnum;
    pf->startflag=0;
    return 0;
}
//子线程函数
void *threadfunc(void *p)
{
    pfactory pf=(pfactory)p;
    pque pq=&pf->que;
    pnode pcur;
    int getsuccess;
    while(1)
    {
        pthread_mutex_lock(&pq->mutex);
        if(!pq->size)
        {
            pthread_cond_wait(&pf->cond,&pq->mutex);
        }
        getsuccess=queget(pq,&pcur);//该函数的返回值，如果队列为空返回-1
        pthread_mutex_unlock(&pq->mutex);
        if(!getsuccess)
        {
            tranfile(pcur->newfd);
            free(pcur);
        }
        pcur=NULL;
    }
}
int factorystart(pfactory pf)
{
    int i;
    if(!pf->startflag)
    {
        for(i=0;i<pf->threadnum;i++)
        {
            pthread_create(pf->pthid,NULL,threadfunc,pf);
        }
        pf->startflag=1;
    }
    return 0;
}

