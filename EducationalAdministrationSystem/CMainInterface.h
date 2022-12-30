#pragma once
#include "CAchievement.h"
#include "CCourse.h"
#include "CStudent.h"
#include "CTeacher.h"
#include<mysql.h>

// CMainInterface 对话框

class CMainInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CMainInterface)

public:
	CMainInterface(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainInterface();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAININTERFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();

	CTabCtrl m_tab;
	CTeacher m_tea;
	CStudent m_stu;
	CCourse m_cou;
	CAchievement m_ach;
	MYSQL* mysql;

};
