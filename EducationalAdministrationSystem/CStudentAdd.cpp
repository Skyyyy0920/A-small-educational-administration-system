// CStudentAdd.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CStudentAdd.h"
#include "afxdialogex.h"


// CStudentAdd 对话框

IMPLEMENT_DYNAMIC(CStudentAdd, CDialogEx)

CStudentAdd::CStudentAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENT_ADD, pParent)
	, m_sid(_T("NULL"))
	, m_sname(_T(""))
	, m_ssex(_T(""))
	, m_sage(_T(""))
	, m_smajor(_T(""))
	, m_spho(_T(""))
{
	m_scredit = _T("0");
	mysql = nullptr;
	update = false;
}

CStudentAdd::CStudentAdd(bool update, CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_STUDENT_ADD, pParent)
{
	m_sid = _T("NULL");
	m_sname = _T("");
	m_ssex = _T("");
	m_sage = _T("");
	m_smajor = _T("");
	m_scredit = _T("0");
	mysql = nullptr;
	this->update = update;
}

CStudentAdd::~CStudentAdd()
{
}

void CStudentAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sid);
	DDX_Text(pDX, IDC_EDIT2, m_sname);
	DDX_Text(pDX, IDC_EDIT3, m_ssex);
	DDX_Text(pDX, IDC_EDIT4, m_sage);
	DDX_Text(pDX, IDC_EDIT5, m_smajor);
	DDX_Text(pDX, IDC_EDIT6, m_spho);
}


BEGIN_MESSAGE_MAP(CStudentAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudentAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudentAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStudentAdd 消息处理程序


void CStudentAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新输入的数据
	UpdateData(TRUE);

	if (update == false) {
		//增加操作
		CString str[6];
		str[0] = m_sid;
		str[1] = m_sname;
		str[2] = m_ssex;
		str[3] = m_sage;
		str[4] = m_smajor;
		str[5] = m_spho;
		//str[6] = m_sGPA;

		char query[200];
		USES_CONVERSION;
		sprintf_s(query, "INSERT INTO student VALUES (%s, '%s', '%s', %s, '%s','%s', %s)", T2A(str[0]), T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]), T2A(str[5]), T2A(m_scredit));
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
		str[0] = m_sid;
		str[1] = m_sname;
		str[2] = m_ssex;
		str[3] = m_sage;
		str[4] = m_smajor;
		str[5] = m_spho;
		//str[5] = m_sGPA;

		char query[300];
		USES_CONVERSION;
		sprintf_s(query, "UPDATE student SET s_name = '%s', s_sex = '%s', s_age = %s, s_major = '%s', s_pho = '%s' WHERE s_id = %s", T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]), T2A(str[5]), T2A(str[0]));
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


void CStudentAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//重置输入
	m_sid = "";
	m_sname = "";
	m_ssex = "";
	m_sage = "";
	m_smajor = "";
	UpdateData(FALSE);
}
