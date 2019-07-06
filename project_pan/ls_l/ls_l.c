#include <func.h>

int ls_l(char *path)
{
    DIR *dir;
    dir=opendir(path);
    ERROR_CHECK(path,NULL,"opendir");
    struct dirent *p;
    char times[1024]={0};
    struct stat s;
    stat(path,&s); 
    while((p=readdir(dir))!=NULL)//为啥p！=NULL就不行，会无限循环
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
            continue;
        }
        strcpy(times,ctime(&s.st_mtime));
        times[strlen(times)-1]='\0';
        printf("%x %ld %s %s %ld %s%s\n",s.st_mode,s.st_nlink,getpwuid(s.st_uid)->pw_name,getgrgid(s.st_gid)->gr_name,s.st_size,ctime(&s.st_mtime),p->d_name);
    }
    closedir(dir);
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    ls_l(argv[1]);
    return 0;
}
