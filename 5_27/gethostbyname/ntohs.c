#include <func.h>

int main()
{
    short port=0x1234;
    short nport;
    nport=htons(port);
    printf("nport=%x\n",nport);
    port=0;
    port=ntohs(nport);
    printf("port=%x\n",port);
    return 0;

}
