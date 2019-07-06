#include <func.h>
#define SHM_HUGE_2MB    1<<21
int main()
{
    int shmid;
    shmid=shmget(1001,SHM_HUGE_2MB,0600|IPC_CREAT|SHM_HUGETLB|SHM_HUGE_2MB);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    return 0;

}
