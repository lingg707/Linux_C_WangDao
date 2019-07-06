#include<func.h>

int main()
{
    
    pid_t pid=fork();
    if(pid==0)
    {
        exit(0);
    }
    if(pid>0)
    {   
        sleep(5);
        pid_t pidd=wait(&pid);
        printf("子进程为：%d",pidd);
        sleep(5);
    }
    return 0;
}
