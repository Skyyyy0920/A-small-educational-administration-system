// CTeacherAdd.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CTeacherAdd.h"
#include "afxdialogex.h"
#include<string.h>


// CTeacherAdd 对话框

IMPLEMENT_DYNAMIC(CTeacherAdd, CDialogEx)

CTeacherAdd::CTeacherAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEACHER_ADD, pParent)
{
	m_tid = _T("NULL");
	m_tname = _T("");
	m_tsex = _T("");
	m_tage = _T("");
	m_tmajor = _T("");
	m_tsalary = _T("");
	mysql = nullptr;
	update = false;
}

CTeacherAdd::CTeacherAdd(bool update, CWnd* pParent /*= nullptr*/) 
	: CDialogEx(IDD_TEACHER_ADD, pParent)
{
	m_tid = _T("NULL");
	m_tname = _T("");
	m_tsex = _T("");
	m_tage = _T("");
	m_tmajor = _T("");
	m_tsalary = _T("");
	mysql = nullptr;
	this->update = update;
}

CTeacherAdd::~CTeacherAdd()
{
}

void CTeacherAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tid);
	DDX_Text(pDX, IDC_EDIT2, m_tname);
	DDX_Text(pDX, IDC_EDIT3, m_tsex);
	DDX_Text(pDX, IDC_EDIT4, m_tage);
	DDX_Text(pDX, IDC_EDIT5, m_tmajor);
	DDX_Text(pDX, IDC_EDIT6, m_tsalary);
}


BEGIN_MESSAGE_MAP(CTeacherAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeacherAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeacherAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTeacherAdd 消息处理程序


void CTeacherAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新输入的数据
	UpdateData(TRUE);

	if (update == false) {
		//增加操作
		CString str[6];
		str[0] = m_tid;
		str[1] = m_tname;
		str[2] = m_tsex;
		str[3] = m_tage;
		str[4] = m_tmajor;
		str[5] = m_tsalary;

		char query[200];
		USES_CONVERSION;
		sprintf_s(query, "INSERT INTO teacher VALUES (%s, '%s', '%s', %s, '%s', %s)", T2A(str[0]), T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]), T2A(str[5]));
		mysql_query(mysql, "SET NAMES GBK");//设置编码格式,否则cmd下中文乱码
		if (mysql_query(mysql, query)) {
			CString error;
			error.Format(L"添加失败,请核对插入的字段是否有误,错误信息:\n%hs", (LPSTR)(LPCTSTR)mysql_error(mysql));
			MessageBox(error);
		}
		else {
			MessageBox(L"添加成功");
		}
	}
	else {
		//修改操作
		CString str[6];
		str[0] = m_tid;
		str[1] = m_tname;
		str[2] = m_tsex;
		str[3] = m_tage;
		str[4] = m_tmajor;
		str[5] = m_tsalary;

		char query[300];
		USES_CONVERSION;
		sprintf_s(query, "UPDATE teacher SET t_name = '%s', t_sex = '%s', t_age = %s, t_major = '%s', t_salary = %s WHERE t_id = %s", T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]), T2A(str[5]), T2A(str[0]));
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


void CTeacherAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//重置输入
	m_tid = "";
	m_tname = "";
	m_tsex = "";
	m_tage = "";
	m_tmajor = "";
	m_tsalary = "";
	UpdateData(FALSE);
}
