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
        //������,�����ظ�����
        return true;
    }

    //��ʼ�����ݿ���
    mysql_init(mysql);

    return mysql_real_connect(mysql, ip, name, password, DBname, port, NULL, 0);
}

bool DataBase::Implement(const char* sentence)
{
    if (false == connection_state) {
        return false;
    }

    //��ѯ����
    sprintf_s(query, "%s", sentence); //desc ����ȡ�ֶ���
    //���ñ����ʽ(SET NAMES GBKҲ��)������cmd���������� 
    mysql_query(mysql, "set names gbk");
    //ִ��SQL���
    if (mysql_query(mysql, query)) {
        printf("Query failed (%s)\n", mysql_error(mysql));
        return false;
    }

    return true;
}

int DataBase::GetTableField(const char* table_name)
{
    //��ѯ����
    sprintf_s(query, "desc %s", table_name); //desc ����ȡ�ֶ���

    //���ñ����ʽ(SET NAMES GBKҲ��)������cmd���������� 
    mysql_query(mysql, "set names gbk");

    //��ѯ�ɹ�����0����ѯʧ�ܷ���1  
    if (mysql_query(mysql, query))    //ִ��SQL���
    {
        printf("Query failed (%s)\n", mysql_error(mysql));
        return false;
    }

    //����������Ϊ�ֶθ���
    return mysql_affected_rows(mysql);
}

bool DataBase::QueryTable(const char* table_name)
{
    if (false == connection_state) return false;

    //��ȡ�ֶ���
    int field = GetTableField(table_name);
    //��ѯ����
    sprintf_s(query, "select * from %s", table_name); //ִ�в�ѯ��� 
    //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd���������� 
    mysql_query(mysql, "set names gbk");

    //����0��ѯ�ɹ�������1��ѯʧ��  
    if (mysql_query(mysql, query)) {
        return false;
    }

    //���sql�������󷵻صĽ����
    res = mysql_store_result(mysql);

    //��ӡ��������  
    printf("number of dataline returned: %lld\n", field);
    //��ȡ�ֶε���Ϣ  
    char* str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ  
    for (int i = 0; i < field; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
    {
        str_field[i] = mysql_fetch_field(res)->name;
    }
    for (int i = 0; i < field; i++)  //��ӡ�ֶ�  
    {
        printf("%10s\t", str_field[i]);
    }
    printf("\n");
    //��ӡ��ȡ������  
    while (_column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡ����ӡ��һ��  
    {
        for (int i = 0; i < field; i++)
        {
            printf("%10s\t", _column[i]);  //column��������  
        }
        printf("\n");
    }

    return true;
}