#pragma once
#include<mysql.h>

class DataBase
{
public:
    DataBase();
    ~DataBase();
    //连接数据库 参数为ip 用户名 密码 数据库名 端口号(如3306)
    bool Connect(const char* ip, const char* name, const char* cypher, const char* database_name, const int port);
    //获取表内的字段数
    int GetTableField(const char* table_name);
    //查询表 参数为表名
    bool QueryTable(const char* table_name);
    //自由执行指令
    bool Implement(const char* sentence);
private:
    bool connection_state;//连接状态 true为已连接
    MYSQL* mysql;//mysql连接  
    MYSQL_FIELD* _fd;//字段列数组  
    char _field[32][32];//存字段名二维数组  
    MYSQL_RES* res;//这个结构代表返回行的一个查询结果集  
    MYSQL_ROW _column;//一个行数据的类型安全(type-safe)的表示，表示数据行的列  
    char query[150];//查询语句

};


