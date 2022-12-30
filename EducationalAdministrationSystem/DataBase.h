#pragma once
#include<mysql.h>

class DataBase
{
public:
    DataBase();
    ~DataBase();
    //�������ݿ� ����Ϊip �û��� ���� ���ݿ��� �˿ں�(��3306)
    bool Connect(const char* ip, const char* name, const char* cypher, const char* database_name, const int port);
    //��ȡ���ڵ��ֶ���
    int GetTableField(const char* table_name);
    //��ѯ�� ����Ϊ����
    bool QueryTable(const char* table_name);
    //����ִ��ָ��
    bool Implement(const char* sentence);
private:
    bool connection_state;//����״̬ trueΪ������
    MYSQL* mysql;//mysql����  
    MYSQL_FIELD* _fd;//�ֶ�������  
    char _field[32][32];//���ֶ�����ά����  
    MYSQL_RES* res;//����ṹ�������е�һ����ѯ�����  
    MYSQL_ROW _column;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
    char query[150];//��ѯ���

};


