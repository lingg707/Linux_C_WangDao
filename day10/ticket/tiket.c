#include<func.h>
typedef struct {
    pthread_mutex_t mutex;
    int ticket;
    pthread_cond_t cont;
}info;
void* sale1(void *p)
{
    info *sale=(info*)p;
    while(1)
    {
        pthread_mutex_lock(&sale->mutex);
        if(sale->ticket>0)
        {
            printf("NO.1,I still have %d tikets\n",sale->ticket);
            sale->ticket--;
            if(sale->ticket==0)
            {
                printf("sales down NO1 need more tikets\n");
                pthread_cond_signal(&sale->cont);  
            }
            pthread_mutex_unlock(&sale->mutex); 
            usleep(1000);
        }
    }
    return NULL;
}
void *sale2(void *p)
{      
    info *sale=(info*)p;
    while(1)
    {   
        pthread_mutex_lock(&sale->mutex);
        if(sale->ticket>0)
        {
            printf("NO.2,I still have %d tikets\n",sale->ticket);
            sale->ticket--;
            if(sale->ticket==0)
            {
                printf("sales down,NO2 need more tikets\n");
                pthread_cond_signal(&sale->cont);
            }
            pthread_mutex_unlock(&sale->mutex);
            usleep(1000);
        }
    }
    return NULL;
}
void* settikets(void* p)
{
    info *sale=(info*)p;
    pthread_mutex_lock(&sale->mutex);
    if(sale->ticket>0)
    {
        pthread_cond_wait(&sale->cont,&sale->mutex);
    }
    sale->ticket=10;
    pthread_mutex_unlock(&sale->mutex);
    return NULL;
}
int main()
{
    pthread_t num1,num2,num3;
    int ret;
    info data;
    data.ticket=20;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_cond_init(&data.cont,NULL);
    ret=pthread_create(&num1,NULL,sale1,&data);
    ret=pthread_create(&num2,NULL,sale2,&data);
    ret=pthread_create(&num3,NULL,settikets,&data);
    pthread_join(num1,NULL);
    pthread_join(num2,NULL);
    pthread_join(num3,NULL);
    printf("main thread,tikets left:%d\n",data.ticket);
    return 0;
}
