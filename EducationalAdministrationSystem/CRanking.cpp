// CRanking.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CRanking.h"
#include "afxdialogex.h"


// CRanking 对话框

IMPLEMENT_DYNAMIC(CRanking, CDialogEx)

CRanking::CRanking(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANKING, pParent)
{
	mysql = NULL;
}

CRanking::~CRanking()
{
}

void CRanking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listcontrol);
}


BEGIN_MESSAGE_MAP(CRanking, CDialogEx)
END_MESSAGE_MAP()


// CRanking 消息处理程序


BOOL CRanking::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//清空表格数据
	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}

	//设置表格风格(list control)
	m_listcontrol.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);

	//查询
	char query[300];
	USES_CONVERSION;
	sprintf_s(query, "%s", "SELECT * FROM view_grade");
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码
	if (mysql_query(mysql, query))return FALSE;//查询语句,如果发生错误,返回FALSE

	MYSQL_RES* res;
	MYSQL_ROW row;
	int row_num = 0;
	res = mysql_store_result(mysql);
	int field_num = res->field_count;//获取字段数

	//设置列名
	CString s[3]; s[0] = "id"; s[1] = "name"; s[2] = "GPA";
	int i = 0;
	while (i < field_num) {
		m_listcontrol.InsertColumn(i, s[i], LVCFMT_LEFT, 120, i);
		i++;
	}

	//填充数据
	while (row = mysql_fetch_row(res)) {
		CString cs;
		cs = row[0];
		m_listcontrol.InsertItem(row_num, cs);
		for (int j = 1; j < field_num; j++) {
			cs = row[j];
			m_listcontrol.SetItemText(row_num, j, cs);
		}
		row_num++;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
