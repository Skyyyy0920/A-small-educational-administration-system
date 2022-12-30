#pragma once
#include<mysql.h>

// CTeacherQuery 对话框

class CTeacherQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherQuery)

public:
	CTeacherQuery(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherQuery();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEACHER_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_query;
	CListCtrl m_listcontrol;
	afx_msg void OnBnClickedButton1();
	MYSQL* mysql;
};
