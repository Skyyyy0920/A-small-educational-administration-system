// CStudent.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CStudent.h"
#include "afxdialogex.h"


// CStudent 对话框

IMPLEMENT_DYNAMIC(CStudent, CDialogEx)

CStudent::CStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENT, pParent)
	, field_num(0)
	, row_num(0)
{	
	mysql = NULL;
}

CStudent::~CStudent()
{
}

void CStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listcontrol);
}


BEGIN_MESSAGE_MAP(CStudent, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudent::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudent::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CStudent::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CStudent::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CStudent::OnLvnItemchangedList1)
END_MESSAGE_MAP()


BOOL CStudent::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	MYSQL_RES* res;
	MYSQL_ROW row;

	//获取字段数
	mysql_query(mysql, "DESC student");
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


// CStudent 消息处理程序


void CStudent::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CStudentAdd csa;
	csa.mysql = this->mysql;
	csa.DoModal();

	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}
	row_num = 0;
	Exhibition();
	/*if (csa.m_sage != "") {
		Update(csa.m_sid);//如果增加数据了,那么更新展示的内容
	}*/
}


void CStudent::OnBnClickedButton2()
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
	sprintf_s(query, "DELETE FROM student WHERE s_id = %s", T2A(str));
	if (mysql_query(mysql, query)) {
		CString error;
		error.Format(L"删除失败,错误信息:\n%hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
		MessageBox(error);
	}
	else {
		MessageBox(L"删除成功");
	}

	sprintf_s(query, "CALL delete_student(%s)", T2A(str));
	if (mysql_query(mysql, query)) {
		CString error;
		error.Format(L"成绩表更新失败,错误信息:\n%hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
		MessageBox(error);
	}
	else {
		MessageBox(L"成绩表更新成功");
	}

	Update(row);//更新表格,这里使用了函数重载,直接传入行号作为参数
}


void CStudent::OnBnClickedButton3()
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
	CString str[7];
	for (int i = 0; i < field_num; i++) {
		str[i] = m_listcontrol.GetItemText(row, i);
	}
	CStudentAdd csa(true);
	csa.mysql = this->mysql;
	csa.m_sid = str[0];
	csa.m_sname = str[1];
	csa.m_ssex = str[2];
	csa.m_sage = str[3];
	csa.m_smajor = str[4];
	csa.m_spho = str[5];
	//csa.m_tsalary = str[6];
	csa.DoModal();

	int count = m_listcontrol.GetItemCount();
	for (int i = 0; i < count; i++) {
		m_listcontrol.DeleteItem(0);
	}
	row_num = 0;
	Exhibition();
}


void CStudent::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	CTeacherQuery ctq;
	ctq.mysql = this->mysql;
	ctq.DoModal();
}


void CStudent::Exhibition()
{
	// TODO: 在此处添加实现代码.

	//将数据库中的内容展示在表格中
	MYSQL_RES* res;
	MYSQL_ROW row;

	//将数据库中的数据输出到表格
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	mysql_query(mysql, "SELECT * FROM student");
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

void CStudent::Update(CString id)
{
	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码 
	char query[200];
	USES_CONVERSION;
	if (id == "NULL") {
		//如果输入的数据使用默认自增id
		sprintf_s(query, "SELECT * FROM student WHERE s_id IN (SELECT MAX(s_id) FROM student)");
	}
	else {
		sprintf_s(query, "SELECT * FROM student WHERE s_id = %s", T2A(id));
	}
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

void CStudent::Update(int row)
{
	m_listcontrol.DeleteItem(row);
}


void CStudent::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
