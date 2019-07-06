#ifndef __WORKQUE_H
#define __WORKQUE_H
#include "func.h"
typedef struct que_node{
    int newfd;
    struct que_node *next;
}node,*pnode;
typedef struct queue{
    pnode tail,head;
    int max;
    int size;//这个有啥用？？
    pthread_mutex_t mutex;
}que,*pque;
void queinit(pque pq,int max);
void queinsert(pque pq,pnode pnew);
void queget(pque pq,pnode* p);//这里取出的是二级指针
#endif
