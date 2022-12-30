#pragma once
#include<mysql.h>

// CTeacherAdd 对话框

class CTeacherAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherAdd)

public:
	CTeacherAdd(CWnd* pParent = nullptr);   // 标准构造函数
	CTeacherAdd(bool update, CWnd* pParent = nullptr);
	virtual ~CTeacherAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEACHER_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_tid;
	CString m_tname;
	CString m_tsex;
	CString m_tage;
	CString m_tmajor;
	CString m_tsalary;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	MYSQL* mysql;
	bool update;
};
