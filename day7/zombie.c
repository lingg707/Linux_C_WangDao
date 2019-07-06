#include<func.h>

int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf("儿子死了\n");
        exit(0);
    }
    else if(pid>0)
    {
        printf("尸变\n");
        sleep(15);
        printf("98k爆头僵尸\n");
    }
    return  0;
}
