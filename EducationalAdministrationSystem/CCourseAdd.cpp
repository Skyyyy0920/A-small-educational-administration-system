// CCourseAdd.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CCourseAdd.h"
#include "afxdialogex.h"


// CCourseAdd 对话框

IMPLEMENT_DYNAMIC(CCourseAdd, CDialogEx)

CCourseAdd::CCourseAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COURSE_ADD, pParent)
	, m_cid(_T("NULL"))
	, m_cname(_T(""))
	, m_cmajor(_T(""))
	, m_credit(_T(""))
	, m_ctype(_T(""))
{
	mysql = nullptr;
	update = false;
}

CCourseAdd::CCourseAdd(bool update, CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_COURSE_ADD, pParent)
{
	m_cid = _T("NULL");
	m_cname = _T("");
	m_credit = _T("");
	m_ctype = _T("");
	m_cmajor = _T("");
	mysql = nullptr;
	this->update = update;
}

CCourseAdd::~CCourseAdd()
{
}

void CCourseAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cid);
	DDX_Text(pDX, IDC_EDIT2, m_cname);
	DDX_Text(pDX, IDC_EDIT3, m_credit);
	DDX_Text(pDX, IDC_EDIT4, m_ctype);
	DDX_Text(pDX, IDC_EDIT5, m_cmajor);
}


BEGIN_MESSAGE_MAP(CCourseAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCourseAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCourseAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCourseAdd 消息处理程序


void CCourseAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新输入的数据
	UpdateData(TRUE);

	if (update == false) {
		//增加操作
		CString str[6];
		str[0] = m_cid;
		str[1] = m_cname;
		str[2] = m_credit;
		str[3] = m_ctype;
		str[4] = m_cmajor;

		char query[200];
		USES_CONVERSION;
		sprintf_s(query, "INSERT INTO course VALUES (%s, '%s', %s, '%s', '%s')", T2A(str[0]), T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]));
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
		str[0] = m_cid;
		str[1] = m_cname;
		str[2] = m_credit;
		str[3] = m_ctype;
		str[4] = m_cmajor;

		char query[300];
		USES_CONVERSION;
		sprintf_s(query, "UPDATE course SET c_name = '%s', c_credit = %s, c_type = '%s', c_major = '%s' WHERE c_id = %s", T2A(str[1]), T2A(str[2]), T2A(str[3]), T2A(str[4]), T2A(str[0]));
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


void CCourseAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//重置输入
	m_cid = _T("");
	m_cname = _T("");
	m_credit = _T("");
	m_ctype = _T("");
	m_cmajor = _T("");
	UpdateData(FALSE);
}
