#include<func.h>

int main()
{
    pid_t pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("pid=%d pidd=%d uid=%d gid=%d euid=%d egid=%d\n",pid,ppid,getuid(),getgid(),geteuid(),getegid());
    return 0;

}
