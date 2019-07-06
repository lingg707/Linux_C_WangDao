#include <func.h>
void* threadFunc(void* p1)
{
    time_t now;
    now=time(NULL);
    char timeBuf[128];
    char *p=ctime_r(&now,timeBuf);
    printf("child thread %s\n",p);
    sleep(5);
    printf("child thread %p %s\n",p,p);
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    PTHREAD_ERROR_CHECK(0,"pthread_create");
    sleep(3);
    time_t now;
    now=time(NULL);
    char *p=ctime(&now);
    printf("main thread %p %s\n",p,p);
    ret=pthread_join(pthid,NULL);
    PTHREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}
