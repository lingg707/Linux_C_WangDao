#include<func.h>
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}h;
void* threadfunc(void *p)
{
    h* data=(h*)p;
    int ret;
    pthread_mutex_lock(&data->mutex);
    ret=pthread_cond_wait(&data->cond,&data->mutex);
    pthread_mutex_unlock(&data->mutex);
    printf("child pthread:id is:%d\n",ret);
    pthread_exit(NULL);
}
int main()
{
    h da;
    pthread_mutex_init(&da.mutex,NULL);
    pthread_cond_init(&da.cond,NULL);
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,&da);
    int ret;
    usleep(1000);
    ret=pthread_cond_signal(&da.cond);
    PTHREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    printf("signal fine\n");
    pthread_join(pthid,NULL);
    return 0;
}
