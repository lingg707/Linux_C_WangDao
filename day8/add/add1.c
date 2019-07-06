#include <func.h>
#define N 10000000

int main()
{
    int shmid;
    shmid=shmget(1000,4096,0777|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    int *p=(int*)shmat(shmid,NULL,0);
    *p=0;
    int i;
    printf("%d\n",*p);
    if(!fork())
    {
        for(i=0;i<N;i++)
            *p+=1;
    }
    else
    {
        for(i=0;i<N;i++)
        {
            *p+=1;
        }
        wait(NULL);
        printf("result=%d\n",*p);
    }
    return 0;
}
