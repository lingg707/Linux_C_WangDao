#include<func.h>

void* threadfunc(void* p)
{   
    while(1){
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    printf("child thread,before wait\n");
    pthread_cond_wait(&cond,&mutex);
    printf("child after wait\n");
    pthread_exit(NULL);
    }
}
int main()
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_t cond;
    pthread_cond_init(&cond,NULL);
    pthread_t pthid1;
    printf("main thread\n");
    pthread_create(&pthid1,NULL,threadfunc,NULL);
    sleep(5);
    pthread_cond_signal(&cond);
    sleep(5);
    pthread_cancel(pthid1);
    pthread_join(pthid1,NULL);
    return 0;
}
