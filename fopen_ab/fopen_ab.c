#include <stdio.h>

int main(int argc,char *argv[])
{
    if (argc!=2){
        printf("error argc\n");
        return -1;
    }
    FILE *fp;
    fp=fopen(argv[1],"ab+");
    if(fp==NULL)
    {
        perror("fopen");
        return -1;
    }
    char buf[128]={0};
    fread(buf,sizeof(char),5,fp);
    printf("buf=%s\n",buf);
    fwrite("how",sizeof(char),3,fp);
    fclose(fp);
    return 0;
}

