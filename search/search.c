#include<func.h>
int search(char* path,char* name)
{
    DIR *fp=opendir(path);
    char buf[1024]={0};
    ERROR_CHECK(fp,NULL,"opendir");
    struct dirent *p;
    while((p=readdir(fp))!=NULL)
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
            continue;//啥也不干
        if(p->d_type==4)
        {
            sprintf(buf,"%s%s%s",path,"/",p->d_name);
            search(p->d_name,name);
        }
        if(strcmp(p->d_name,name))
        {
            printf("%s\n",name);
            printf("%s\n",getcwd(NULL,0));
            break;
        }
    }
    closedir(fp);
    return 0;
}

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    search(argv[1],argv[2]);

}
