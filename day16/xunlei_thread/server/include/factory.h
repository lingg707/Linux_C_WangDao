#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "workque.h"
#include "head.h"
typedef struct{
    que que;
    pthread_cond_t cond;
    pthread_t *pthid;
    int threadnum;
    int startflag;
}factory,*pfactory;

#endif
