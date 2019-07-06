#include<func.h>
int main()
{
    char buf[1024];
    char *pret;
    pret=getcwd(buf,sizeof(buf));
    ERROR_CHECK(pret,NULL,"getcwd");
    printf("buf=%s\n",buf);
    printf("path=%s\n",getcwd(NULL,0));
    return 0;
}
