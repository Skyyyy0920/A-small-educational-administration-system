#pragma once
#include<mysql.h>
#include"CTeacherAdd.h"
#include"CTeacherQuery.h"

// CTeacher 对话框

class CTeacher : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher)

public:
	CTeacher(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacher();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEACHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	void Exhibition();
	void Update(CString id);
	void Update(int row);

	MYSQL* mysql;
	CListCtrl m_listcontrol;
	int field_num;//字段数
	int row_num;//数据行数
};
