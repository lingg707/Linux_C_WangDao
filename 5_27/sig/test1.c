#include<func.h>

void sigfunc(int signum)
{
    printf("signum at begin:%d\n",signum);
    sleep(2);
    printf("signum at end:%d\n",signum);
}
int main()
{
    signal(SIGINT,sigfunc);
    //signal(SIGQUIT,sigfunc);
    while(1);
    return 0;
}
