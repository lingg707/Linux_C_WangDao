#include <func.h>
typedef struct{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;
void* saleWindows1(void* p)
{
    threadInfo_t *pSale=(threadInfo_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pSale->mutex);
        if(pSale->tickets>0)
        {
            printf("I am saleWindows1,I will sale tickets %d\n",pSale->tickets);
            pSale->tickets--;
            if(!pSale->tickets)
            {
                pthread_cond_signal(&pSale->cond);
            }
            printf("I am saleWindows1,sale finish %d\n",pSale->tickets);
            pthread_mutex_unlock(&pSale->mutex);
            usleep(1000);

        }else{
            pthread_mutex_unlock(&pSale->mutex);
            break;
        }
    }
    return NULL;
}
void* saleWindows2(void* p)
{
    threadInfo_t *pSale=(threadInfo_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pSale->mutex);
        if(pSale->tickets>0)
        {
            printf("I am saleWindows2,I will sale tickets %d\n",pSale->tickets);
            pSale->tickets--;
            if(!pSale->tickets)
            {
                pthread_cond_signal(&pSale->cond);
            }
            printf("I am saleWindows2,sale finish %d\n",pSale->tickets);
            pthread_mutex_unlock(&pSale->mutex);
            usleep(1000);
        }else{
            pthread_mutex_unlock(&pSale->mutex);
            break;
        }
    }
    return NULL;
}
void* setTickets(void *p)
{
    threadInfo_t *pSet=(threadInfo_t*)p;
    pthread_mutex_lock(&pSet->mutex);
    if(pSet->tickets>0)
    {
        pthread_cond_wait(&pSet->cond,&pSet->mutex);
    }
    pSet->tickets=20;
    pthread_mutex_unlock(&pSet->mutex);
    return NULL;
}
int main()
{
    pthread_t pthid1,pthid2,pthid3;
    int ret;
    threadInfo_t data;
    data.tickets=20;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_cond_init(&data.cond,NULL);
    ret=pthread_create(&pthid1,NULL,saleWindows2,&data);
    ret=pthread_create(&pthid2,NULL,saleWindows1,&data);
    ret=pthread_create(&pthid3,NULL,setTickets,&data);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    pthread_join(pthid3,NULL);
    printf("I am main threadckets=%d\n",data.tickets);
    return 0;
}


