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
    struct msgbuf msg;
    msg.mtype=1;
    strcpy(msg.mtext,"hello world");
    printf("mtext=%s\n",msg.mtext);
    int ret=msgsnd(msgid,&msg,strlen(msg.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}
