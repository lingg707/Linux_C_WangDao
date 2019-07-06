#include<func.h>

void freemem(void * args)
{
    printf("I'm free function\n");
    free(args);
    printf("I've cleande up the memory\n");    
}
void* threadfunc(void *args)
{
    char* p=(char*)malloc(10);
    pthread_cleanup_push(freemem,p);//第二个参数传入第一个参数
    strcpy(p,"helloworld");//子线程分配空间
    printf("before free :child thread puts:%s\n",p);
    sleep(1);//不知道sleep有啥用
    pthread_exit((void*)3);//这句应该是被忽略的，没什么用
    pthread_cleanup_pop(0);//参数为0时，必须前面调用exit接口，才可以正常清理
}
int main()
{
    pthread_t pthid;
    int reti=pthread_create(&pthid,NULL,threadfunc,NULL);
    if(reti!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(reti));
        return -1;
    }
    printf("main thread\n");
    sleep(1);//不知道sleep有啥用
    int retc= pthread_cancel(pthid);
    PTHREAD_ERROR_CHECK(retc,"pthread_cancel");
    int ret=0;
    pthread_join(pthid,(void**)&ret);
    printf("child thread returns %d\n",ret);//cancel子线程返回为-1，因此cancel函数执行成功
    return 0;
}
