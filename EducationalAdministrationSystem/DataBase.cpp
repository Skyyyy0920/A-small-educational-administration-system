#include "pch.h"
#include "DataBase.h"

DataBase::DataBase()
{
    connection_state = false;
    mysql = new MYSQL;
    _fd = nullptr;
    memset(_field, NULL, sizeof(_field));
    res = nullptr;
    _column = nullptr;
    memset(query, NULL, sizeof(query));
}

DataBase::~DataBase() 
{

}

bool DataBase::Connect(const char* ip, const char* name, const char* password, const char* DBname, const int port) 
{
    if (connection_state == true) {
        //已连接,无需重复连接
        return true;
    }

    //初始化数据库句柄
    mysql_init(mysql);

    return mysql_real_connect(mysql, ip, name, password, DBname, port, NULL, 0);
}

bool DataBase::Implement(const char* sentence)
{
    if (false == connection_state) {
        return false;
    }

    //查询内容
    sprintf_s(query, "%s", sentence); //desc 语句获取字段数
    //设置编码格式(SET NAMES GBK也行)，否则cmd下中文乱码 
    mysql_query(mysql, "set names gbk");
    //执行SQL语句
    if (mysql_query(mysql, query)) {
        printf("Query failed (%s)\n", mysql_error(mysql));
        return false;
    }

    return true;
}

int DataBase::GetTableField(const char* table_name)
{
    //查询内容
    sprintf_s(query, "desc %s", table_name); //desc 语句获取字段数

    //设置编码格式(SET NAMES GBK也行)，否则cmd下中文乱码 
    mysql_query(mysql, "set names gbk");

    //查询成功返回0，查询失败返回1  
    if (mysql_query(mysql, query))    //执行SQL语句
    {
        printf("Query failed (%s)\n", mysql_error(mysql));
        return false;
    }

    //数据行数即为字段个数
    return mysql_affected_rows(mysql);
}

bool DataBase::QueryTable(const char* table_name)
{
    if (false == connection_state) return false;

    //获取字段数
    int field = GetTableField(table_name);
    //查询内容
    sprintf_s(query, "select * from %s", table_name); //执行查询语句 
    //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码 
    mysql_query(mysql, "set names gbk");

    //返回0查询成功，返回1查询失败  
    if (mysql_query(mysql, query)) {
        return false;
    }

    //获得sql语句结束后返回的结果集
    res = mysql_store_result(mysql);

    //打印数据行数  
    printf("number of dataline returned: %lld\n", field);
    //获取字段的信息  
    char* str_field[32];  //定义一个字符串数组存储字段信息  
    for (int i = 0; i < field; i++)  //在已知字段数量的情况下获取字段名  
    {
        str_field[i] = mysql_fetch_field(res)->name;
    }
    for (int i = 0; i < field; i++)  //打印字段  
    {
        printf("%10s\t", str_field[i]);
    }
    printf("\n");
    //打印获取的数据  
    while (_column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行  
    {
        for (int i = 0; i < field; i++)
        {
            printf("%10s\t", _column[i]);  //column是列数组  
        }
        printf("\n");
    }

    return true;
}