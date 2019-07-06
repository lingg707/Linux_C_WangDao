#include<func.h>
#define N 10000000
void* threadFunc(void* p)
{
    int *sum=(int*)p;
    int i=0;
    for(i=0;i<N;i++)
    {
        *sum=*sum+1;
    }
    return NULL;
}
int main()
{
    pthread_t pthid;
    int sum=0;
    int ret=pthread_create(&pthid,NULL,threadFunc,&sum);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    int i=0;
    for(i=0;i<N;i++)
        sum=sum+1;
    pthread_join(pthid,NULL);
    printf("main thread:%d\n",sum);
    return 0;
}
