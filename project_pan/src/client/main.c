#include "func.h"
#define N 256
int ret;
int SigHandler(int iSignNo)                    
{
    printf("%dsig was captured\n",iSignNo);
    return 2;
}
int main(int argc,char* argv[])
{
    //建立客户端的socket
    ARGS_CHECK(argc,3);
    int socketfd;
    tcpinit_c(&socketfd,argv[1],argv[2]);//连接完成,内含connect函数，已经连接成功

    com_help();
    while(1)
    {
        printf("i am login func\n");
        login();//1、这里需要用send和recv传递
        break;
    }
    //int ret;
    while(1)
    {
    char comd[8]={0};
        //int signum;
       /* ret=signal(SIGINT,SigHandler);
        if(ret==2)
        {
            printf("send exit successfully\n");
            char sif[5]="exit";
            send(socketfd,sif,5,0);
            break;
        }*/
        printf("client>");
        fflush(stdout);//这一句加了了有什么效果？
        //ret=fgets(comd,7,stdin);
        if(fgets(comd,7,stdin)==NULL)//fget函数的返回值是char *型的，因此不能直接用ret判断
        {
            printf("fgets error\n");
            return -1;
        }
        comd[strlen(comd)-1]='\0';
        //2、这里直接传给服务器
        ret=send(socketfd,comd,strlen(comd),0);//命令传给了服务器
        if(ret!=-1)
        {
            printf("send成功\n");
        }
        //printf("%s\n",comd);

        if(strncmp(comd,(char*)"ls",2)==0)
        {
            com_ls(socketfd);
            printf("\n");
        }
        else if(strncmp(comd,(char*)"cd",2)==0)
        {
            com_cd();
        }
        else if(strncmp(comd,(char*)"put",3)==0)
        {
            com_put();
        }
        else if(strncmp(comd,(char*)"get",3)==0)
        {
            com_get();
        }
        else if(strncmp(comd,(char*)"help",4)==0)
        {
            com_help();
        }
        else if(strncmp(comd,(char*)"exit",4)==0)
        {
            com_exit();
        }
        else
            printf("command error! Try Again\n");
    }
    //void login();//用recv，send函数
    // void com_send();
    // void recvcycle();//传出命令之后，服务器传回，然后客户端打印
    //欢迎界面。报告连接完成，请进行command函数
    //switch循环，实现命令的传递
    printf("i am client end\n");
    return 0;
}


//以下的所有全部封装成函数，实现传递命令
//传递文件名和大小
/*int datalen;
  char buf[1000]={0};
  recv(socketfd,&datalen,4,MSG_WAITALL);
  ret=recv(socketfd,buf,datalen,MSG_WAITALL);
  if(ret<=0)
  {
  perror("recv");
  return -1;
  }
//传递文件
off_t filesize=0;//用来确定文件大小
recv(socketfd,&datalen,4,MSG_WAITALL);//标志位表示所有要求都满足的>
ret=recv(socketfd,&filesize,datalen,MSG_WAITALL);
if(ret<=0)
{
perror("recv");
return -1;
}
printf("fileSize=%ld\n",filesize);
//打开文件
int fd;
fd=open(buf,O_RDWR|O_CREAT,0666);
ERROR_CHECK(fd,-1,"open");
ret=ftruncate(fd,filesize);
if(ret!=0)
{
perror("ftruncate");
return -1;
}
//mmap函数
char *pMap=(char*)mmap(NULL,filesize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
ERROR_CHECK(pMap,(char*)-1,"mmap");
recvcycle(socketfd,pMap,filesize);
ret=munmap(pMap,filesize);
ERROR_CHECK(ret,-1,"munmap");

close(fd);
close(socketfd);
}*/
