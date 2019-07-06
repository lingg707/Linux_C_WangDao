#ifndef __WORK_QUE__
#define __WORK_QUE__
#include "head.h"
typedef struct tagnode{
    int newfd;
    struct tagnode *pnext;
}node,*pnode;
typedef struct tagque{
    pnode que_head,que_tail;
    int capacity;
    int size;
    pthread_mutex_t mutex;
}que,pque;
void queinit(pque pq,int capacity);
void queinsert(pque pq,pnode pnew);
void queget(pque pq,pnode *p);
#endif
