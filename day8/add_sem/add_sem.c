#include <func.h>
#define N 10000000

int main()
{
    //共享内存区的建立
    key_t key=ftok("./add_sem.c",1);
    ERROR_CHECK(key,-1,"ftok");
    printf("key=%d\n",key);
    int shmid;
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    int *p=(int*)shmat(shmid,NULL,0);//共享内存映射返回的逻辑地址的初始地址
    *p=0;
    int i;
    printf("初始值为：%d\n",*p);
    //信号量的建立
    int semarr=semget(key,1,IPC_CREAT|0600);
    ERROR_CHECK(semarr,-1,"semget");
    int ret;
    ret=semctl(semarr,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sopp,sopv;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    sopv.sem_num=0;
    sopv.sem_op=1;
    sopv.sem_flg=SEM_UNDO;
    //设立计时器
    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(!fork())
    {
        for(i=0;i<N;i++){
            semop(semarr,&sopp,1);
            *p+=1;
            semop(semarr,&sopv,1);
        }
    }
    else
    {
        for(i=0;i<N;i++){
            semop(semarr,&sopp,1);
            *p+=1;
            semop(semarr,&sopv,1);
        }
        wait(NULL);
    }
    gettimeofday(&end,NULL);
    printf("used time in second is %lds\n",end.tv_sec-start.tv_sec);
    printf("result=%d\n used time in um =%ldum\n",*p,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    
    return 0;
}
