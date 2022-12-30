// CTeacher.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CTeacher.h"
#include "afxdialogex.h"


// CTeacher 对话框

IMPLEMENT_DYNAMIC(CTeacher, CDialogEx)

CTeacher::CTeacher(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEACHER, pParent)
	, field_num(0)
	, row_num(0)
{
	mysql = NULL;
}

CTeacher::~CTeacher()
{
}

void CTeacher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_listcontrol);
}


BEGIN_MESSAGE_MAP(CTeacher, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CTeacher::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeacher::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeacher::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTeacher::OnBnClickedButton3)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTeacher::OnLbnSelchangeList1)
END_MESSAGE_MAP()


BOOL CTeacher::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	MYSQL_RES* res;
	MYSQL_ROW row;

	//获取字段数
	mysql_query(mysql, "DESC teacher");
	res = mysql_store_result(mysql);
	field_num = mysql_num_rows(res);

	//设置表格风格(list control)
	m_listcontrol.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);

	//设置列名
	int i = 0;
	while (row = mysql_fetch_row(res)) {
		CString s;
		s = row[0];
		m_listcontrol.InsertColumn(i, s, LVCFMT_LEFT, 120, i);
		i++;
	}

	Exhibition();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// CTeacher 消息处理程序


void CTeacher::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CTeacherAdd cta;
	cta.mysql = this->mysql;
	cta.DoModal();

	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}
	row_num = 0;
	Exhibition();
	//Update(cta.m_tid);//更新展示的内容 5.24:发现一个莫名其妙的bug，有时候能更新，有时候更新不了
}


void CTeacher::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//删除选中的一行数据

	//首先得到点击的位置
	POSITION pos = m_listcontrol.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请至少选择一项", L"提示", MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化
	int row = (int)m_listcontrol.GetNextSelectedItem(pos);
	//获取第row第0列的内容，并保存到str中
	CString str = m_listcontrol.GetItemText(row, 0);

	char query[200];
	USES_CONVERSION;
	sprintf_s(query, "DELETE FROM teacher WHERE t_id = %s", T2A(str));
	if (mysql_query(mysql, query)) {
		CString error;
		error.Format(L"删除失败,错误信息:\n%hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
		MessageBox(error);
	}
	else {
		MessageBox(L"删除成功");
	}

	Update(row);//更新表格,这里使用了函数重载,直接传入行号作为参数
}


void CTeacher::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//首先得到点击的位置
	POSITION pos = m_listcontrol.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请至少选择一项", L"提示", MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化
	int row = (int)m_listcontrol.GetNextSelectedItem(pos);
	//获取第row第0列的内容，并保存到str中
	CString str[6];
	for (int i = 0; i < field_num; i++) {
		str[i] = m_listcontrol.GetItemText(row, i);
	}
	CTeacherAdd cta(true);
	cta.mysql = this->mysql;
	cta.m_tid = str[0]; 
	cta.m_tname = str[1]; 
	cta.m_tsex = str[2]; 
	cta.m_tage = str[3]; 
	cta.m_tmajor = str[4]; 
	cta.m_tsalary = str[5];
	cta.DoModal();

	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}
	row_num = 0;
	Exhibition();
}


void CTeacher::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CTeacherQuery ctq;
	ctq.mysql = this->mysql;
	ctq.DoModal();
}

void CTeacher::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTeacher::Exhibition()
{
	// TODO: 在此处添加实现代码.

	//将数据库中的内容展示在表格中
	MYSQL_RES* res;
	MYSQL_ROW row;

	//将数据库中的数据输出到表格
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	mysql_query(mysql, "SELECT * FROM teacher");
	res = mysql_store_result(mysql);
	while (row = mysql_fetch_row(res)) {
		CString s;
		s = row[0];
		m_listcontrol.InsertItem(row_num, s);
		for (int j = 1; j < field_num; j++) {
			s = row[j];//这里有个小疑问，为啥数据库里的int类型还能正常赋值给string？
			m_listcontrol.SetItemText(row_num, j, s);
		}
		row_num++;
	}
}

void CTeacher::Update(CString id) 
{
	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	char query[200];
	USES_CONVERSION;
	sprintf_s(query, "SELECT * FROM teacher WHERE t_id = %s", T2A(id));
	mysql_query(mysql, query);
	res = mysql_store_result(mysql);
	if (!res)return;
	row = mysql_fetch_row(res);
	CString s;
	s = row[0];
	m_listcontrol.InsertItem(row_num, s);
	for (int j = 1; j < field_num; j++) {
			s = row[j];//这里有个小疑问，为啥数据库里的int类型还能正常赋值给string？
			m_listcontrol.SetItemText(row_num, j, s);
	}
	row_num++;
}

void CTeacher::Update(int row) 
{
	m_listcontrol.DeleteItem(row);
}