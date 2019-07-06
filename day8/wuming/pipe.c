#include<func.h>

int main()
{
    int fds[2];//一个管道的读写端
    pipe(fds);
    if(!fork())
    {
        close(fds[0]);//关闭读
        char buf[128]={"Hello"};
        write(fds[1],buf,strlen(buf));
        printf("child process fds[1]=%d\n",fds[1]);
        exit(0);
    }
    else
    {
        char buf1[128]={0};
        close(fds[1]);//关闭写
        read(fds[0],buf1,5);
        printf("father there %s fds[0]=%d\n",buf1,fds[0]);
        wait(NULL);//等待创建的孩子
    }
    return 0;
}

