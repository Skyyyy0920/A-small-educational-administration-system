#pragma once
#include"CTeacherQuery.h"
#include"CCourseAdd.h"
#include<mysql.h>

// CCourse 对话框

class CCourse : public CDialogEx
{
	DECLARE_DYNAMIC(CCourse)

public:
	CCourse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCourse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	void Exhibition();
	void Update(CString id);
	void Update(int row);

	MYSQL* mysql;
	CListCtrl m_listcontrol;
	int field_num;//字段数
	int row_num;//数据行数	
	
};
