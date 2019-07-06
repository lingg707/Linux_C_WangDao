#include"factory.h"
#include"func.h"
#include"workque.h"

void queinit(pque pq,int max)
{
    memset(pq,0,sizeof(que));
    pq->max=max;
    pthread_mutex_init(&pq->mutex,NULL);
}
void queinsert(pque pq,pnode pnew)
{
    if(pq->head==NULL)
    {
        pq->head=pnew;
        pq->tail=pnew;
    }else{
        pq->tail->next=pnew;
        pq->tail=pnew;
    }
    pq->size++;
}
void queget(pque pq,pnode *pcur)
{
    *pcur=pq->head;
    pq->head=pq->head->next;
    if(pq->head==NULL)
    {
        pq->tail=NULL;
    }
    pq->size--;
}
