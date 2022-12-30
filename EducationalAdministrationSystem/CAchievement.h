#pragma once
#include<mysql.h>
#include"CTeacherQuery.h"
#include"CAchievementAdd.h"
#include"CRanking.h"

// CAchievement 对话框

class CAchievement : public CDialogEx
{
	DECLARE_DYNAMIC(CAchievement)

public:
	CAchievement(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAchievement();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACHIEVEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	virtual BOOL OnInitDialog();
	void Exhibition();
	void Update(CString sid, CString cid);
	void Update(int row);

	CListCtrl m_listcontrol;
	MYSQL* mysql;
	int field_num;//字段数
	int row_num;//数据行数

};
