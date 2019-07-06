#include<func.h>

struct msgbuf
{
    long mtype;
    char mtext[128];
};
int main()
{
    int msgid=msgget(1001,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msg1;
    memset(msg1.mtext,0,sizeof(msg1.mtext));
    printf("mtext=%s\n",msg1.mtext);
    int ret =msgrcv(msgid,&msg1,sizeof(msg1.mtext),0,0);
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("got: %s\n",msg1.mtext);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
