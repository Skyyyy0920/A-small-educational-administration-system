// CMainInterface.cpp: 实现文件
//

#include "pch.h"
#include "EducationalAdministrationSystem.h"
#include "CMainInterface.h"
#include "afxdialogex.h"


// CMainInterface 对话框

IMPLEMENT_DYNAMIC(CMainInterface, CDialogEx)

CMainInterface::CMainInterface(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAININTERFACE, pParent)
{
	mysql = new MYSQL;
}

CMainInterface::~CMainInterface()
{
}

void CMainInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CMainInterface, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainInterface::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMainInterface 消息处理程序


void CMainInterface::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int count;
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_tea.ShowWindow(SW_SHOW);
		m_stu.ShowWindow(SW_HIDE);
		m_cou.ShowWindow(SW_HIDE);
		m_ach.ShowWindow(SW_HIDE);
		count = m_tea.m_listcontrol.GetItemCount();
		for (int i = 0; i < count; i++) {
			m_tea.m_listcontrol.DeleteItem(0);
		}
		m_tea.row_num = 0;
		m_tea.Exhibition();
		break;
	case 1:
		m_tea.ShowWindow(SW_HIDE);
		m_stu.ShowWindow(SW_SHOW);
		m_cou.ShowWindow(SW_HIDE);
		m_ach.ShowWindow(SW_HIDE);
		count = m_stu.m_listcontrol.GetItemCount();
		for (int i = 0; i < count; i++) {
			m_stu.m_listcontrol.DeleteItem(0);
		}
		m_stu.row_num = 0;
		m_stu.Exhibition();
		break;
	case 2:
		m_tea.ShowWindow(SW_HIDE);
		m_stu.ShowWindow(SW_HIDE);
		m_cou.ShowWindow(SW_SHOW);
		m_ach.ShowWindow(SW_HIDE);
		count = m_cou.m_listcontrol.GetItemCount();
		for (int i = 0; i < count; i++) {
			m_cou.m_listcontrol.DeleteItem(0);
		}
		m_cou.row_num = 0;
		m_cou.Exhibition();
		break;
	case 3:
		m_tea.ShowWindow(SW_HIDE);
		m_stu.ShowWindow(SW_HIDE);
		m_cou.ShowWindow(SW_HIDE);
		m_ach.ShowWindow(SW_SHOW);
		count = m_ach.m_listcontrol.GetItemCount();
		for (int i = 0; i < count; i++) {
			m_ach.m_listcontrol.DeleteItem(0);
		}
		m_ach.row_num = 0;
		m_ach.Exhibition();
		break;
	default:
		break;
	}
	
	*pResult = 0;
}


BOOL CMainInterface::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化数据库句柄
	mysql_init(mysql);
	//连接数据库 参数为ip 用户名 密码 数据库名 端口
	mysql_real_connect(mysql, "127.0.0.1", "root", "hth20020315", "educationaladministratorsystem", 0, NULL, 0);
	m_tea.mysql = this->mysql;
	m_stu.mysql = this->mysql;
	m_cou.mysql = this->mysql;
	m_ach.mysql = this->mysql;

	//为Tab Control增加页面
	m_tab.InsertItem(0, _T("教师信息"));
	m_tab.InsertItem(1, _T("学生信息"));
	m_tab.InsertItem(2, _T("课程信息"));
	m_tab.InsertItem(3, _T("成绩信息"));

	//创建对话框
	m_tea.Create(IDD_TEACHER, &m_tab);
	m_stu.Create(IDD_STUDENT, &m_tab);
	m_cou.Create(IDD_COURSE, &m_tab);
	m_ach.Create(IDD_ACHIEVEMENT, &m_tab);

	//设定在tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 8;
	rc.left += 4;
	rc.right -= 4;

	//修改子窗口的位置
	m_tea.MoveWindow(&rc);
	m_stu.MoveWindow(&rc);
	m_cou.MoveWindow(&rc);
	m_ach.MoveWindow(&rc);

	//目前展示的是teacher表
	m_tea.ShowWindow(SW_SHOW);

	//设置当前展示的分页
	m_tab.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
