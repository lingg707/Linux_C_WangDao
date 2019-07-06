#include <sys/stat.h>       
#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<signal.h>
#include<sys/wait.h>
#include<pthread.h>
#include<malloc.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include <sys/epoll.h>
#include<sys/uio.h>

#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error argc\n");return -1;}}
#define ERROR_CHECK(ret,retval,funName) {if(ret==retval) {perror(funName);return -1;}}
#define PTHREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return -1;}} 

typedef struct{
    pid_t pid;
    int fds;//全双工管道
    short busy;//1忙碌，0非忙碌
}ProcessData_t,*pProcessData_t;

int makechild(pProcessData_t,int);
int childhandle(int);
int tcpinit(int *,char *,char *);
int sendfd(int,int);
int recvfd(int,int*);






