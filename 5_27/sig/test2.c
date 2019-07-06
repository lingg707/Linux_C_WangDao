#include <func.h>

void sigFunc(int sigNum, siginfo_t *p, void* p1)
{
    printf("before sleep %d\n", sigNum);
    sleep(3);
    printf("after sleep %d\n", sigNum);

}

int main()
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigFunc;
    int ret = sigaction(SIGINT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction");
    ret = sigaction(SIGQUIT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction");
    while(1);
    return 0;
}

