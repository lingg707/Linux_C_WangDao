#include<func.h>
struct msgbuf
{
    long mtype;
    char mtext[128];
};
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msg;
    msg.mtype=atoi(argv[1]);
    strcpy(msg.mtext,argv[2]);
    msgsnd(msgid,&msg,strlen(msg.mtext),0);
    return 0;
}
