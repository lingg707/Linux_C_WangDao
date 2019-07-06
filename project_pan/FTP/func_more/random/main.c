#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//注释里面的语句如果执行，则不会出现NULL错误
#define STR_LEN 10//定义随机输出的字符串长度。
//char *GenerateStr(char **a)
char *GenerateStr(char *a)
{
    char str[STR_LEN + 1] = {0};
    int i,flag;
    srand(time(NULL));
    for(i = 0; i < STR_LEN; i ++)
    {
        flag = rand()%3;
        switch(flag)
        {
        case 0:
            str[i] = rand()%26 + 'a'; 
            break;
        case 1:
            str[i] = rand()%26 + 'A'; 
            break;
        case 2:
            str[i] = rand()%10 + '0'; 
            break;
        }
    }
    printf("%s\n", str);//输出生成的随机数。
    //*a= str;
    a= str;
    return 0;
}
int main()
{

    char *a=NULL;
    //GenerateStr(&a);
    GenerateStr(a);//不用二重指针传值，输出的结果就是NULL，指针的值并不会改，只能用二重指针
    printf("mainfunc output :%s\n",a);
    return 0;
}
