#include<func.h>

int main()
{
    key_t key=ftok("./Makefile",1);
    ERROR_CHECK(key,-1,"ftok");
    int shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    printf("gets data from shm:%s\n",p);
    if(shmctl(shmid,IPC_RMID,0)==-1)
    {
        perror("shmctl");
        exit(-1);
    }
    return 0;
}
