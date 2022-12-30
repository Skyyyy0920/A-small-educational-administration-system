#pragma once
#include<mysql.h>

// CRanking 对话框

class CRanking : public CDialogEx
{
	DECLARE_DYNAMIC(CRanking)

public:
	CRanking(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRanking();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANKING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listcontrol;
	virtual BOOL OnInitDialog();
	MYSQL* mysql;
};
