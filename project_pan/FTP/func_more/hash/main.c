#include "hash.h"
#include "common.h"

typedef struct stu
{
    char sno[5];
    char name[32];
    int age;

}stu_t;

typedef struct stu2
{
    int sno;
    char name[32];
    int age;

}stu2_t;
//字符串哈希函数
unsigned int hash_str(unsigned int buckets,void *key)
{
    char *sno=(char *)key;
    unsigned int index=0;
    while(*sno)
    {
        index=*sno+4*index;
        sno++;
    }

    return index % buckets;
}

unsigned int hash_int(unsigned int buckets,void *key)
{
    int *sno=(int *)key;
    return (*sno) % buckets;
}

int main()
{
    /*
       stu_t stu_arr[]=
       {
       {"1234","AAAA",20},
       {"4568","AAAA",23},
       {"6729","AAAA",19}
       };
       hash_t  *hash=hash_alloc(256,hash_str);
       int size=sizeof(stu_arr)/sizeof(stu_arr[0]);
       int i;
       for(i=0;i<size;i++)
       {//插入地址,关键码,关键码的长度，数据项
       hash_add_entry(hash,stu_arr[i].sno,strlen(stu_arr[i].sno),
       &stu_arr[i],sizeof(stu_arr[i]));
       }
    //查找
    stu_t *s=(stu_t *)hash_lookup_entry(hash,"4568",strlen("4568"));
    if(s)
    {
    printf("%s %s %d\n",s->sno,s->name,s->age);
    }
    else
    printf("Not found\n");

    hash_free_entry(hash,"1234",strlen("1234"));
    s=(stu_t *)hash_lookup_entry(hash,"1234",strlen("1234"));
    if(s)
    {
    printf("%s %s %d\n",s->sno,s->name,s->age);
    }
    else
    printf("Not found\n");
    */

    stu2_t stu_arr[]=
    {
        {1234,"AAAA",20},
        {4568,"AAAA",23},
        {6729,"AAAA",19}
    };

    hash_t  *hash=hash_alloc(256,hash_int);

    int size=sizeof(stu_arr)/sizeof(stu_arr[0]);
    int i;
    for(i=0;i<size;i++)
    {//插入地址,关键码,关键码的长度，数据项
        hash_add_entry(hash,&(stu_arr[i].sno),sizeof(stu_arr[i].sno),
                       &stu_arr[i],sizeof(stu_arr[i]));
    }
    //查找
    int sno=4568;
    stu2_t *s=(stu2_t *)hash_lookup_entry(hash,&sno,sizeof(sno));
    if(s)
    {
        printf("%d %s %d\n",s->sno,s->name,s->age);
    }
    else
        printf("Not found\n");

    sno=1234;
    hash_free_entry(hash,&sno,sizeof(sno));

    s=(stu2_t *)hash_lookup_entry(hash,&sno,sizeof(sno));
    if(s)
    {
        printf("%d %s %d\n",s->sno,s->name,s->age);
    }
    else
        printf("Not found\n");
    return 0;
}

--------------------- 
作者：NK_test 
来源：CSDN 
原文：https://blog.csdn.net/nk_test/article/details/50526184 
版权声明：本文为博主原创文章，转载请附上博文链接！
}
}
}
}
}
}
}
}
}
}
