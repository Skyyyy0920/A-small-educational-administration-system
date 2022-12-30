// CAchievement.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CAchievement.h"
#include "afxdialogex.h"


// CAchievement 对话框

IMPLEMENT_DYNAMIC(CAchievement, CDialogEx)

CAchievement::CAchievement(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACHIEVEMENT, pParent)
	, field_num(0)
	, row_num(0)
{
	mysql = NULL;
}

CAchievement::~CAchievement()
{
}

void CAchievement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listcontrol);
}


BEGIN_MESSAGE_MAP(CAchievement, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAchievement::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAchievement::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAchievement::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAchievement::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CAchievement::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAchievement::OnBnClickedButton6)
END_MESSAGE_MAP()


BOOL CAchievement::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	MYSQL_RES* res;
	MYSQL_ROW row;

	//获取字段数
	mysql_query(mysql, "DESC score");
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


// CAchievement 消息处理程序


void CAchievement::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CAchievementAdd csa;
	csa.mysql = this->mysql;
	csa.DoModal();

	Update(csa.m_sid, csa.m_cid);//更新展示的内容
}


void CAchievement::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	POSITION pos = m_listcontrol.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请至少选择一项", L"提示", MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化
	int row = (int)m_listcontrol.GetNextSelectedItem(pos);
	//获取第row行第0列的内容，并保存到str中
	CString str1 = m_listcontrol.GetItemText(row, 0);
	CString str2 = m_listcontrol.GetItemText(row, 1);

	char query[200];
	USES_CONVERSION;
	sprintf_s(query, "DELETE FROM score WHERE s_id = %s AND c_id = %s", T2A(str1), T2A(str2));
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


void CAchievement::OnBnClickedButton3()
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
	CString str[4];
	for (int i = 0; i < field_num; i++) {
		str[i] = m_listcontrol.GetItemText(row, i);
	}
	CAchievementAdd caa(true);
	caa.mysql = this->mysql;
	caa.m_sid = str[0];
	caa.m_cid = str[1];
	caa.m_tid = str[2];
	caa.m_score = str[3];
	CString score_old = str[3];
	caa.DoModal();

	USES_CONVERSION;
	char query[200];
	sprintf_s(query, "SELECT c_credit FROM course WHERE c_id = %s", T2A(str[1]));
	mysql_query(mysql, query);

	MYSQL_RES* res;
	MYSQL_ROW myrow;

	res = mysql_store_result(mysql);
	myrow = mysql_fetch_row(res);
	CString credit;
	credit = myrow[0];

	sprintf_s(query, "CALL update_credit2(%s, %s, %s, %s)", T2A(str[0]), T2A(caa.m_score), T2A(score_old), T2A(credit));
	if (mysql_query(mysql, query)) {
		CString error;
		error.Format(L"更新失败,请核对插入的字段是否有误");
		MessageBox(error);
	}
	else {
		MessageBox(L"学生表更新成功");
	}

	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}
	row_num = 0;
	Exhibition();
}


void CAchievement::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CTeacherQuery ctq;
	ctq.mysql = this->mysql;
	ctq.DoModal();
}


void CAchievement::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAchievement::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	CRanking cr;
	cr.mysql = this->mysql;
	cr.DoModal();
}


void CAchievement::Exhibition()
{
	// TODO: 在此处添加实现代码.

	//将数据库中的内容展示在表格中
	MYSQL_RES* res;
	MYSQL_ROW row;

	//将数据库中的数据输出到表格
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	mysql_query(mysql, "SELECT * FROM score");
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

void CAchievement::Update(CString sid, CString cid)
{
	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	char query[200];
	USES_CONVERSION;
	sprintf_s(query, "SELECT * FROM score WHERE s_id = %s AND c_id = %s", T2A(sid), T2A(cid));
	mysql_query(mysql, query);
	res = mysql_store_result(mysql);
	if (!res)return;
	row = mysql_fetch_row(res);
	CString s;
	if (!row)return;
	s = row[0];
	m_listcontrol.InsertItem(row_num, s);
	for (int j = 1; j < field_num; j++) {
		s = row[j];//这里有个小疑问，为啥数据库里的int类型还能正常赋值给string？
		m_listcontrol.SetItemText(row_num, j, s);
	}
	row_num++;
}

void CAchievement::Update(int row)
{
	m_listcontrol.DeleteItem(row);
}


