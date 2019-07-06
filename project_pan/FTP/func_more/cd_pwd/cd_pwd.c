#include<func.h>
#define PATH_SIZE 100
#define BUF_SIZE 64
int cds(const char *p)
{
    char path[PATH_SIZE];
    char *start;
    char *end;
    int res;
    //int n= 0;

    memset(path,'\0',PATH_SIZE); // must init 
    start = strchr(p,' ');
    end = strchr(p,'\n');
    if(!start || !end)
    {
        printf("can't support this format \n");
        return 1;
    }

    strncpy(path,p+3,end-start-1); // get the path in inputting command
    res = chdir(path); //change dir
    if(res != 0)
        printf("%s is nod a path,please check again \n",path);

    return res;
}
int pwds()
{
    char buf[PATH_SIZE];
    char *res;

    res = getcwd(buf,PATH_SIZE);
    if(res)
    {
        printf("%s\n",buf);
        return 0;
    }
    else
        return 1;
}
int main(int argc, char *argv[])
{
    while(1){
        char buf[BUF_SIZE]={0};
        printf("|->");
        fgets(buf,BUF_SIZE,stdin);
        if(strncmp(buf,"pwd",3)==0)
        {
            printf("the direction is\n");
            pwds();
            continue;
        }
        else{
            cds(buf);
            printf("CD successfully,the directory now is:\n");
            pwds();
        }
    }
}

