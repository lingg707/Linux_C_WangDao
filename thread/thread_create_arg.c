#include<func.h>
void print()
{
    printf("this is print function\n");
    //exit中的参数为自然返回值，被其他线程用join捕获
    pthread_exit((void*)2);//2作为返回值被pthread_join捕获
}
//线程的创建入口函数
void* threadFunc(void* p)
{
    printf("child thread returns when created :%s\n",(char*)p);
    print();
    printf("after print function :\n");
    free(p);
    return NULL;
}
int main()
{
    pthread_t pthid;//这个id是子线程的id
    char *p=(char *)malloc(20);
    strcpy(p,"1");
    int ret=pthread_create(&pthid,NULL,threadFunc,p);
    if(ret!=0)
    {
        printf("%s:%s\n","pthread_create",strerror(ret));
        return -1;
    }
    int rete=0;
    printf("this is main thread\n");
    //线程从入口点函数自然返回时，函数返回值可以被其他线程用join函数获取
    pthread_join(pthid,(void**)&rete);//第二个参数是二重指针
    printf("child exit and it returns:%d\n",rete);
    return 0;
}
