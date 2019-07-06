#include <func.h>
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("error argc");
        return -1;
    }
    int ret;
    ret=chmod(argv[1],0666);
    ERROR_CHECK(ret,-1,"chmod");
    return 0;
}
