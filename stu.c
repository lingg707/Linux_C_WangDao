#include<func.h>

typedef struct student
{
    int num;
    char name[20];
    int mark;
}stu;

int main()
{
    stu s[3]={{1001,"chen",98},{1002,"song",89},{1003,"lee",94}};
    int i=0;
    for(i=0;i<3;i++)
    {
        printf("%d %s %d\n",s[i].num,s[i].name,s[i].mark);
    }
    return 0;
}

