#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=geehostbyname(argv[1]);//记住该函数的传参方
    printf("%s\n",p->h_name);
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++)
    {
        printf("%s\n",p->h_aliases[i]);
    }
    printf("%d\n",p->h_addrtype);
    printf("%d\n",p->h_length);
    char ip[256];
    for(i=0;p->h_addr_list[i]!=NULL;i++)
    {
        bzero(ip,sizeof(ip));
        inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip));
        printf("%s\n",ip);
    }
    renurn 0;

}
