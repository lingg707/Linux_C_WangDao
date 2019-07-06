#include<func.h>

int main()
{
    pid_t s=fork();
    if(s==0)
    {
        printf("son process pid=%d\nparent process pid=%d\n",getpid(),getppid());
        while(1);
    }
    if(s<0)
    {
        printf("error!");
    }
    else
    {
        while(1);
    }
    return 0;
}
