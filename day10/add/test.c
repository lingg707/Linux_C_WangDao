#include <func.h>
void* threadFunc(void* p)
{
    printf("I am child thread\n");
    return NULL;
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;

    }
    printf("I am main thread,my thread id=%ld\n",pthread_self());
    usleep(100);
    while(1);
    pthread_join(pthid,NULL);
    return 0;

}
