#include <func.h>
#define SHM_HUGE_2MB 1<<21
int main()
{
    key_t key=("./huge.c",1);
    ERROR_CHECK(key,-1,"ftok");
    int shmid=shmget(key,SHM_HUGE_2MB,0600|IPC_CREAT|SHM_HUGETLB|SHM_HUGE_2MB);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    return 0;
}
