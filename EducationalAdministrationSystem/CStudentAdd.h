#pragma once
#include<mysql.h>

// CStudentAdd 对话框

class CStudentAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentAdd)

public:
	CStudentAdd(CWnd* pParent = nullptr);   // 标准构造函数
	CStudentAdd(bool update, CWnd* pParent = nullptr);
	virtual ~CStudentAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sid;
	CString m_sname;
	CString m_ssex;
	CString m_sage;
	CString m_smajor;
	CString m_spho;
	CString m_scredit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	MYSQL* mysql;
	bool update;
	
};
