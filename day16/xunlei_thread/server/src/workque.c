#include "workque.h"
void queinit(pque pq,int capacity)
{
    memset(pq,0,sizeof(que));
    pq->capacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
}
void queinsert(pque pq,pnode pnew)//入队，从队尾入队
{
    if(NULL==pq->que_head)
    {
        pq->que_head=pnew;
        pq->que_tail=pnew;
    }else{
        pq->que_tail->pnext=pnew;
        pq->que_tail=pnew;
    }
    pq->size++;
}
int queget(pque pq,pnode* pget)//出队，如果为空报错，pget为二级指针，factory主函数直接用pget传参
{
    *pget=pq->que_head;
    if(NULL==*pget)
    {
        return -1;
    }
    pq->que_head=pq->que_head->pnext;
    if(NULL==pq->que_head)
    {
        pq->que_tail=NULL;
    }
    pq->size--;
    return 0;
}
