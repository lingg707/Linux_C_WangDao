#include<func.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        printf("child,pid=%d ppid=%d %d\n",getpid(),getppid(),iStack);
    }
    else{
        printf("father\n");
        sleep(1);
    }
    return 0;
}
