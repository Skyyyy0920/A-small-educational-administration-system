// CAchievementAdd.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CAchievementAdd.h"
#include "afxdialogex.h"


// CAchievementAdd 对话框

IMPLEMENT_DYNAMIC(CAchievementAdd, CDialogEx)

CAchievementAdd::CAchievementAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACHIEVEMENT_ADD, pParent)
	, m_sid(_T(""))
	, m_cid(_T(""))
	, m_tid(_T(""))
	, m_score(_T(""))
{
	mysql = nullptr;
	update = false;
}

CAchievementAdd::CAchievementAdd(bool update, CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_COURSE_ADD, pParent)
{
	m_sid = _T("");
	m_cid = _T("");
	m_tid = _T("");
	m_score = _T("");
	mysql = nullptr;
	this->update = update;
}

CAchievementAdd::~CAchievementAdd()
{
}

void CAchievementAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sid);
	DDX_Text(pDX, IDC_EDIT2, m_cid);
	DDX_Text(pDX, IDC_EDIT3, m_tid);
	DDX_Text(pDX, IDC_EDIT4, m_score);
}


BEGIN_MESSAGE_MAP(CAchievementAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAchievementAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAchievementAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAchievementAdd 消息处理程序


void CAchievementAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新输入的数据
	UpdateData(TRUE);

	if (update == false) {
		//增加操作
		CString str[5];
		str[0] = m_sid;
		str[1] = m_cid;
		str[2] = m_tid;
		str[3] = m_score;

		char query[200];
		USES_CONVERSION;
		sprintf_s(query, "INSERT INTO score VALUES (%s, %s, %s, %s)", T2A(str[0]), 
			T2A(str[1]), T2A(str[2]), T2A(str[3]));
		mysql_query(mysql, "SET NAMES utf8mb4");//设置编码格式,否则cmd下中文乱码
		if (mysql_query(mysql, query)) {
			CString error;
			//error.Format(L"添加失败,请核对插入的字段是否有误,错误信息:\n%hs", mysql_error(mysql));
			error.Format(L"添加失败,请核对插入的字段是否有误");
			MessageBox(error);
			return;
		}
		else {
			MessageBox(L"添加成功");
		}

		//获取当前插入的数据对应课程的学分
		sprintf_s(query, "SELECT c_credit FROM course WHERE c_id = %s", T2A(str[1]));
		mysql_query(mysql, query);

		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_store_result(mysql);
		row = mysql_fetch_row(res);
		CString credit;
		credit = row[0];

		sprintf_s(query, "CALL update_credit(%s, %s, %s)", T2A(str[0]), T2A(str[3]), T2A(credit));
		if (mysql_query(mysql, query)) {
			CString error;
			error.Format(L"更新失败,请核对插入的字段是否有误");
			MessageBox(error);
		}
		else {
			MessageBox(L"学生表更新成功");
		}
	}
	else {
		//修改操作
		CString str[6];
		str[0] = m_sid;
		str[1] = m_cid;
		str[2] = m_tid;
		str[3] = m_score;

		char query[300];
		USES_CONVERSION;
		sprintf_s(query, "UPDATE score SET t_id = %s, score = %s WHERE s_id = %s AND c_id = %s", 
			T2A(str[2]), T2A(str[3]), T2A(str[0]), T2A(str[1]));
		if (mysql_query(mysql, query)) {
			CString error;
			error.Format(L"更新失败, 错误信息:\n % hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
			MessageBox(error);
		}
		else {
			MessageBox(L"更新成功");
		}
	}
}


void CAchievementAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//重置输入
	m_sid = _T("");
	m_cid = _T("");
	m_tid = _T("");
	m_score = _T("");
	UpdateData(FALSE);
}
