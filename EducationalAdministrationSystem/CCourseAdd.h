#pragma once
#include<mysql.h>

// CCourseAdd 对话框

class CCourseAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CCourseAdd)

public:
	CCourseAdd(CWnd* pParent = nullptr);   // 标准构造函数
	CCourseAdd(bool update, CWnd* pParent = nullptr);
	virtual ~CCourseAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSE_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cid;
	CString m_cname;
	CString m_credit;
	CString m_ctype;
	CString m_cmajor;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	MYSQL* mysql;
	bool update;
};
