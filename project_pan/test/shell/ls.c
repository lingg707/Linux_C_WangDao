#include<func.h>                                                    
int ls_l(char *path)
{
    DIR *dir;
    dir=opendir(path);
    ERROR_CHECK(path,NULL,"opendir");
    struct dirent *p;
    char times[1024]={0};
    struct stat s;
    stat(path,&s);
    int n;
    while((p=readdir(dir))!=NULL)
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
            continue;
        }
    stat(path,&s);
        strcpy(times,ctime(&s.st_mtime));
        times[strlen(times)-1]='\0';
        for(n=8;n>=0;n--)          
        {     
            if(s.st_mode&(1<<n))  
            {  
                switch(n%3)   
                {        
                case 2:             printf("r");   
                                    break;    
                case 1:             printf("w");    
                                    break;     
                case 0:             printf("x");    
                                    break; 
                default:    
                                    break;     
                } 
            }  
            else      
            {  
                printf("-"); 
            } 
        }
        printf(" %ld %s %s %ld %s %s\n",s.st_nlink,getpwuid(s.st_uid)->pw_name,getgrgid(s.st_gid)->gr_name,s.st_size,ctime(&s.st_mtime),p->d_name);
    }
    // closedir(dir);
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    ls_l(argv[1]);
    return 0;
}
