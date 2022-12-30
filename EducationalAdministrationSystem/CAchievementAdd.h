#pragma once
#include<mysql.h>

// CAchievementAdd 对话框

class CAchievementAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CAchievementAdd)

public:
	CAchievementAdd(CWnd* pParent = nullptr);   // 标准构造函数
	CAchievementAdd(bool update, CWnd* pParent = nullptr);
	virtual ~CAchievementAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACHIEVEMENT_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sid;
	CString m_cid;
	CString m_tid;
	CString m_score;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	MYSQL* mysql;
	bool update;
};
