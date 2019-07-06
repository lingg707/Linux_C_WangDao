#ifndef __FUNC_H__
#define __FUNC_H__
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


#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error argc\n");return -1;}}
#define ERROR_CHECK(ret,retval,funName) {if(ret==retval) {perror(funName);return -1;}}
#define PTHREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return -1;}}
int tcpinit(int *,char *,char *);
int tcpinit_c(int*,char*,char*);
int recvcycle(int,void*,int);
int login();
/*int sigfunc(int signum)                    
{
    printf("%dsig was captured\n",signum);
    return 2;
}*/
int com_ls(int);
void com_cd();
void com_put();
void com_get();
void com_exit();
void com_help();
#endif
