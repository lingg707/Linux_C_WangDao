#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pwd.h>
#define NUM 1024
#define SIZE 50
int mystrtok(char *argv[],char *string);
int mystrtok(char *argv[],char *string)
{
    int i=0;
    char delim[]=" ";
    //char *p;
    argv[0]=strtok(string,delim);//字符串分割函数的使用
    //printf("this is strtokfunc1 %s\n",argv[0]);
    while(argv[i]!=NULL)
    {
        printf("strtokfunc argv[%d]=%s\n",i,argv[i]);
        i++;
        argv[i]=strtok(NULL,delim);
        //printf("this is strtok func2%s is %d\n",argv[i],i);
    }
    return 0;
}
//获得一个命令提示符的字符串
char *getusername(char buffer[NUM])
{
    uid_t userid;
    char *username;
    char *hostname;
    char *ptr,*p;
    char buf1[1024],buf2[1024];
    char *delim=(char*)".";
    int id;
    getcwd(buf2,100);//这段代码说明的是对命令提示的路径获得
    username=getenv("USER");//调用getenv函数，来获得shell命令的提示中的用户名
    strcpy(buffer,username);
    strcat(buffer,"@");
    id=gethostname(buf1,sizeof(buf1));//调用此函数来获取shell命令的提示中的主机名
    p=strtok(buf1,delim);//对主机进行截取
    strcat(buffer,p);//字符串的连接函数
    ptr=strrchr(buf2,(char)'/');//字符串的从后往前进行截取的函数，讲多得shell命令提示中的路径
    //比较字符串，判断用户的路径是在"/","~",还是其他当中
    if(strcmp(ptr,"/")==0)
    {
        ptr=(char*)"/";
    }
    else if(strcmp(ptr,"~")==0)
    {
        ptr=(char*)"~";
    }
    else
    {
        ptr=strtok(ptr,"/");
    }
    //把获得的 [用户名@主机名  路径]连接在一起
    strcat(buffer," ");
    strcat(buffer,ptr);
    return buffer;
}
int main()
{
    pid_t pid;
    int status;
    char *argv[NUM];
    char buffer[NUM];
    char str[NUM];
    int j=-1;
    char *string=NULL;
    string=getenv("USER");
    //当前用户是root用户还是普通用户,通过字符串的比较，如果是root，则返回0；
    if((strcmp(string,"root"))==0)
    {
        j=0;
    }
    while(1){
        //通过调用上面自定义的getusername（）函数，来得到shell命令中的提示
        printf("[%s]",getusername(buffer));

        //判断是使用root的提示#，还是其他用户的$
        if(j==0)
        {
            printf("# ");
        }
        else
        { 
            printf("$ ");
        }
        //字符串的输入，要用gets函数或者用fgets函数，因为scanf函数把空格看成字符串的结束
        //gets(str);
        fgets(str,100,stdin);
        //调用字符串的分割函数，获得要截取出来的命令和命令参数，例如：ls -a分别放到argv[0],argv[1]中
        status=mystrtok(argv,str);
        if(status!=0)
        {
            printf("fail to getargv!\n");
        }
        //通过fork（）函数来创建一个父进程和一个子进程
        pid=fork();
        if(-1==pid)
        {
            printf("your fork failed!\n");
        } 
        else if(pid==0)
        { 
            //子进程用来对shell命令进程进程解释执行的
            if(argv[1]!=NULL)
            {
                execvp(argv[0],argv);
            }
            else if(argv[1]==NULL)
            {
                execlp(argv[0],argv[0],NULL,NULL);
            }
        }
        else
        {
            //父进程用来等待子进程的结束，然后再循环输入shell命令
            if(wait(&status)==-1)
            {
                printf("wait failed!\n");
                exit(1);
            }
        }
    }
    return 0;
}
