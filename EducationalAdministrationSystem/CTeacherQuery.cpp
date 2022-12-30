// CTeacherQuery.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CTeacherQuery.h"
#include "afxdialogex.h"


// CTeacherQuery 对话框

IMPLEMENT_DYNAMIC(CTeacherQuery, CDialogEx)

CTeacherQuery::CTeacherQuery(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEACHER_QUERY, pParent)
	, m_query(_T(""))
{
	mysql = NULL;
}

CTeacherQuery::~CTeacherQuery()
{
}

void CTeacherQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_query);
	DDX_Control(pDX, IDC_LIST1, m_listcontrol);
}


BEGIN_MESSAGE_MAP(CTeacherQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeacherQuery::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTeacherQuery 消息处理程序


void CTeacherQuery::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新数据
	UpdateData(true);

	m_query.Replace(L"script", L"");
	m_query.Replace(L"src", L"");
	m_query.Replace(L"-", L"");
	m_query.Replace(L"1=1", L"");
	m_query.Replace(L"1 = 1", L"");
	m_query.Replace(L"1= 1", L"");
	m_query.Replace(L"1 =1", L"");

	//CString CHECKSQL = " ^ (. + )\\sand\\s(. + ) | (. + )\\sor(. + )\\s$";
	//Pattern.matches(CHECKSQL, targerStr);
	//检测SQL meta - characters的正则表达式 ：/ (\ % 27) | (\’) | (\ - \ - ) | (\ % 23) | (#) / ix
	//修正检测SQL meta - characters的正则表达式 ： / ((\ % 3D) | (= ))[^ \n] * ((\ % 27) | (\’) | (\ - \ - ) | (\ % 3B) | (:)) / i
	//典型的SQL 注入攻击的正则表达式 ： / \w * ((\ % 27) | (\’))((\ % 6F) | o | (\ % 4F))((\ % 72) | r | (\ % 52)) / ix
	//检测SQL注入，UNION查询关键字的正则表达式 ： / ((\ % 27) | (\’))union / ix(\ % 27) | (\’)
	//检测MS SQL Server SQL注入攻击的正则表达式：	/ exec(\s | \ + ) + (s | x)p\w + / ix

	//清空表格数据
	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}

	//设置表格风格(list control)
	m_listcontrol.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);

	//将查询结果打印到表格
	char query[300];
	USES_CONVERSION;
	sprintf_s(query, "%s", T2A(this->m_query));
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码
	if (mysql_query(mysql, query)) {
		CString error;
		error.Format(L"执行失败,请检查查询语句是否有误,错误信息:\n%hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
		MessageBox(error);
		return;
	}
	else {
		MessageBox(L"查询成功");
	}

	MYSQL_RES* res;
	MYSQL_ROW row;
	int row_num = 0;
	res = mysql_store_result(mysql);
	int field_num = res->field_count;//获取字段数

	//设置列名
	int i = 0;
	while (i <= field_num) {
		CString s;
		s.Format(L"%d", i);
		m_listcontrol.InsertColumn(i, s, LVCFMT_LEFT, 120, i);
		i++;
	}

	//填充数据
	while (row = mysql_fetch_row(res)) {
		CString s;
		s = row[0];
		m_listcontrol.InsertItem(row_num, s);
		for (int j = 1; j < field_num; j++) {
			s = row[j];
			m_listcontrol.SetItemText(row_num, j, s);
		}
		row_num++;
	}
}
