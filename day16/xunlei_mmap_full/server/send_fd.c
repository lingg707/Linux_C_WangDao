#include "process_pool.h"
int sendfd(int fds,int fd)
{
    //进程间描述符的传递
    struct msghdr msg;
    memset(&msg,0,sizeof(struct msghdr));
    struct iovec iov[2];//结构体数组
    iov[0].iov_base="hello";
    iov[0].iov_len=5;//结构体数组的数量
    iov[1].iov_base="world";//随便写啥都行
    iov[1].iov_len=5;
    msg.msg_iov=iov;//用户态的校验，是啥不清楚
    msg.msg_iovlen=2;//有两个成员
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);//给指针赋值，一定要提前分配空间
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;//拿到cmsg最后一个成员的起始地址，强转成整形指针再解引用，得到最后一个成员的空间，这就是变长结构体
    msg.msg_control=cmsg;//变长结构体
    msg.msg_controllen=len;
    int ret=sendmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
//一般情况下，子进程得到的描述符为主进程传入的值+1，即引用计数加一，因为指向的是同一个文件对象
int recvfd(int fds,int *fd)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    char buf1[10]={0};//用来接hello和world，sengmsg里写的
    char buf2[10]={0};
    struct iovec iov[2];
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret=recvmsg(fds,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(cmsg);//与前一个函数，相比，倒过来，最后的fd就是要传的文件描述符
    return 0;
}
