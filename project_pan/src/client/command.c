//client
#include "func.h"

void com_help()
{
    printf("--------WELCOME TO PROJECT_PAN--------\n");
    printf("Project_pan Client VERSION 1.0.0\n");
    printf("Server ip:192.168.4.143;Server port:2000\n");
    printf("commands are listed as below,instructions are followed\n");
    printf("   help:  Display all the commands\n");
    printf("   ls  :  Display all the documents and directions in server\n");
    printf("   cd  :  Exchange current direction\n");
    printf("   put :  Put documents in your disks onto Server\n");
    printf("   get :  Download documents you upload before\n");
    printf("   exit:  Quit the process\n");
}
int login()
{
    //char ;
    printf("Please enter USERNAME:");
    //fgets("");
    printf("Please enter PASSWORD:");
    printf("LOGIN SUCCESS\n");
    printf("LOGIN FAILED,PLEASE ENTER AGAIN\n");
    return 0;
}
int com_ls(int sfd)
{
    int ret;
    printf("i am ls\n");
    char buf[2048]={0};
        printf("enter recv func\n");
       ret=recv(sfd,buf,2048,0);
       printf("%d",ret);
        printf("%s",buf);
        memset(buf,0,2048);
        if(ret<=0)
    if(ret<0)
    {
        perror("recv");
    }
    return 0;
}
void com_cd()
{
    printf("i am cd\n");
}
void com_put()
{
    printf("i am put \n");
}
void com_get()
{
    printf("i am get\n");
}
void com_exit()
{
    printf("i am exit\n");
}
