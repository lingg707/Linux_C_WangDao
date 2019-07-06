#ifndef __FACTORY_H__
#define __FACTORY_H__
//定义结构体的意义，传值只能是一个值，因此只能传一个值
#include"func.h"
#include"workque.h"
typedef struct{
    que queue;
    pthread_cond_t cond;
    pthread_t *pthid;
    int flag;
    int threadnum;
}factory,*pfactory;
#define FILENAME "file"
int factoryinit(pfactory,int,int);
int factorystart(pfactory);
void *threadfunc(void*);
typedef struct {
    int datalen;
    char buf[1000];
}train;
int transfile(int);
int login();
int com_ls(int);
void com_cd();
void com_put();
void com_get();
void com_exit();
void com_help();
#endif
