#include<func.h>

int main()
{
    key_t key=ftok("./Makefile",1);
    ERROR_CHECK(key,-1,"ftok");
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);//第一个数值填1000即可，第二个大小最好是4k的整数倍，0600表示可读可写
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    memset(p,0,4096);
    strcpy(p,"hello world");
    if(shmdt(p)==-1)
    {
        perror("shmdt");
        exit(-1);
    }
    return 0;
}

