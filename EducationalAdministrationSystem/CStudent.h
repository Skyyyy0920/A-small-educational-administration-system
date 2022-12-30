#pragma once
#include"CStudentAdd.h"
#include"CTeacherQuery.h"
#include<mysql.h>


// CStudent 对话框

class CStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CStudent)

public:
	CStudent(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudent();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	void Exhibition();
	void Update(CString id);
	void Update(int row);

	MYSQL* mysql;
	CListCtrl m_listcontrol;
	int field_num;//字段数
	int row_num;//数据行数
	
};
