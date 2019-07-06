#include <func.h>
#define N 20000000

typedef struct{
    int sum;
    pthread_mutex_t mutex;
}thread;
void* threadFunc(void* p)
{
    thread *data=(thread*)p;
    int i;
    sleep(1);
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&data->mutex);
        data->sum+=1;
        pthread_mutex_unlock(&data->mutex);
    }
    printf("child thread,the outcome is :%d\n",data->sum);
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    thread data;
    data.sum=0;
    ret=pthread_mutex_init(&data.mutex,NULL);
    PTHREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    PTHREAD_ERROR_CHECK(ret,"pthread_create");
    int i;
   // usleep(5000);//在这里加sleep能保证公平调度
    //整体能看出来，第一次是main先占有cpu，之后两者随机
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&data.mutex);
        data.sum+=1;
        pthread_mutex_unlock(&data.mutex);
    }
    printf("main thread outcome is: %d\n",data.sum);
    sleep(0);//这里没屌用
    pthread_join(pthid,NULL);
    return 0;
}
