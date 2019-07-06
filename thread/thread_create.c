#include<func.h>

void* threadFunc(void* p)
{
    printf("child thread\n");//线程开始函数
}
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    printf("main thread\n");
    usleep(100);
    return 0;
}
