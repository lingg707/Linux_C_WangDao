#ifndef __FACTORY_H__
#define __FACTORY_H__
#include"head.h"
#include "workque.h"
typedef struct{
    que que;
    pthread_cond_t cond;
    pthread_t *pthid;
    int threadnum;
    int startflag;
}factory,*pfactory;
typedef struct{
    int datalen;
    char buf[1000];
}train;
#define FILENAME "file"
int factoryinit(pfactory,int,int);
int factorystart(pfactory);
int tcpinit(int *sfd,char* ip,char* port);
int tranfile(int);
#endif
