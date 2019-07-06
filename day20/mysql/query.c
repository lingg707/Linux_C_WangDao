#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;

    }
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="root";
    char* database="mydb2";//要访问的数据库名称
    char query[300]="select * from course where name='";
    sprintf(query,"%s%s%s",query, argv[1],"'");
    /* strcpy(query,"select * from person"); */
    puts(query);
    int t,r;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;

    }else{
        printf("Connected...\n");

    }
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));

    }else{
        printf("query success\n");

    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));

    }else{
        //  printf("Query made...\n");
        res=mysql_use_result(conn);
        if(res)
        {
            printf("use result\n");
            while((row=mysql_fetch_row(res))!=NULL)
            {   
                for(t=0;t<mysql_num_fields(res);t++)
                {
                    printf("%8s ",row[t]);
                }
                printf("\n");
            }
        }else{
            printf("Don't find data\n");
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
    return 0;
}
