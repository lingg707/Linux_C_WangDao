#include<func.h>
typedef struct student
{
    int num;
    char name[20];
    float mark;
}stu;
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);
    ERROR_CHECK(fd,-1,"open");
    stu s[3]={{1001,"lee",96.5},{1002,"lele",76.8},{1003,"liang",87.5}};
    char buf[1024]={0};
    int i=0;
    for(i=0;i<3;i++)
    {
        sprintf(buf,"%d %s %5.2f\n",s[i].num,s[i].name,s[i].mark);//以字符串的形式 存储到buf里面
        write(fd,buf,strlen(buf));//不能直接格式化的写入文件中，因此要用sprintf
    }
    lseek(fd,0,SEEK_SET);
    while(read(fd,buf,strlen(buf))>0);
    printf("%s",buf);
    return 0;
}
