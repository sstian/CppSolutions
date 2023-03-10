// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"

SAdmin CLoginDlg::m_firstAdmin = { _T("admin"), _T("admin"), 1 };

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(TIMER_1, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	COleDateTime oletime = COleDateTime::GetTickCount();
	CString strtime;
	strtime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"),
		oletime.GetYear(), oletime.GetMonth(), oletime.GetDay(), oletime.GetHour(), oletime.GetMinute(), oletime.GetSecond());
	SetDlgItemText(IDC_DATETIME, strtime);

	CDialogEx::OnTimer(nIDEvent);
}



//pWnd: 当前鼠标位于哪个窗口（控件）上，可以通过pWnd->GetDlgCtrID()来判断设置鼠标形状
//nHitTest: 表示当前鼠标位于实现该函数的窗口的哪个位置(HTBORDER HTCLIENT等等，参考OnNcHitTest函数)
//message: 表示鼠标消息的值（WM_LBUTTONDOWN  WM——LBUTTONUP诸如此类）
BOOL CLoginDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	switch (nHitTest)
	{
	case HTCAPTION:
		SetDlgItemText(IDC_STATUS, _T("Login Dialog"));
		break;
	default:
		break;
	}

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_USERNAME:
		SetDlgItemText(IDC_STATUS, _T("请在此处输入用户名"));
		break;
	case IDC_EDIT_PASSWORD:
		SetDlgItemText(IDC_STATUS, _T("请在此处输入密码"));
		break;
	default:
		break;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
//// WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
//#define HTERROR             (-2)			//在屏幕背景或窗口之间的分隔线上（与HTNOWHERE相同，除了Windows的DefWndProc函数产生一个系统响声以指明错误）
//#define HTTRANSPARENT       (-1)			//在一个被其它窗口覆盖的窗口中
//#define HTNOWHERE           0				//在屏幕背景或窗口之间的分隔线上
//#define HTCLIENT            1				//在客户区中
//#define HTCAPTION           2				//在标题条中
//#define HTSYSMENU           3				//在控制菜单或子窗口的关闭按钮上
//#define HTGROWBOX           4				//在尺寸框中
//#define HTSIZE              HTGROWBOX
//#define HTMENU              5				//菜单区域
//#define HTHSCROLL           6				//在水平滚动条上
//#define HTVSCROLL           7				//在垂直滚动条中
//#define HTMINBUTTON         8				//在最小化按钮上
//#define HTMAXBUTTON         9				//在最大化按钮上
//#define HTLEFT              10			//在窗口的左边框上
//#define HTRIGHT             11			//在窗口的右边框上
//#define HTTOP               12			//在窗口水平边框的上方
//#define HTTOPLEFT           13			//在窗口边框的左上角
//#define HTTOPRIGHT          14			//在窗口边框的右上角
//#define HTBOTTOM            15			//在窗口的水平边框的底部
//#define HTBOTTOMLEFT        16			//在窗口边框的左下角
//#define HTBOTTOMRIGHT       17			//在窗口边框的右下角
//#define HTBORDER            18			//在不具有可变大小边框的窗口的边框上
//#define HTREDUCE            HTMINBUTTON
//#define HTZOOM              HTMAXBUTTON
//#define HTSIZEFIRST         HTLEFT
//#define HTSIZELAST          HTBOTTOMRIGHT
//#define HTOBJECT            19
//#define HTCLOSE             20
//#define HTHELP              21
//LRESULT CWnd::OnNcHitTest(CPoint) { return Default(); }

void CLoginDlg::OnBnClickedOk()
{
	SetDlgItemText(IDC_STATUS, _T(""));
	NextDlgCtrl();
	int ctrlID = GetFocus()->GetDlgCtrlID();
	if (IDOK == ctrlID || IDC_EDIT_USERNAME == ctrlID)
	{
		CString username;
		CString password;
		GetDlgItemText(IDC_EDIT_USERNAME, username);
		GetDlgItemText(IDC_EDIT_PASSWORD, password);
		if (!this->CheckPass(username, password))	//username != _T("admin") || password != _T("admin")
		{
			SetDlgItemText(IDC_STATUS, _T("残念：用户名或密码错误！"));
			SetFocus();		//设置焦点于第一个控件上
			return;
		}
		SetDlgItemText(IDC_STATUS, _T("登录成功，欢迎光临"));
		CDialogEx::OnOK();
		KillTimer(TIMER_1);
	}
}

// 检查用户名与密码匹配
BOOL CLoginDlg::CheckPass(CString& username, CString& password)
{
	CFile file;
	SAdmin admin;
	BOOL flag = FALSE;
	if (!file.Open(ADMIN_DATA, CFile::modeRead))		//打开文件
	{
		//AfxMessageBox(_T("File open failed!"));
		this->CreateUser();								//失败了则创建第一人（因为不存在）
		if (!file.Open(ADMIN_DATA, CFile::modeRead))	//再次打开
			return FALSE;
	}
	while (sizeof(admin) == file.Read(&admin, sizeof(admin)))
	{	//!username.Compare(admin.sname) && !password.Compare(admin.spass)
		if (!(username.Compare(admin.sname) || password.Compare(admin.spass)))
		{
			theApp.m_user = admin;	//传递登录用户数据，以在其它类中使用，通过唯一全局对象theApp
			flag = TRUE;
			break;
		}
	}
	file.Close();	//CFile的析构函数中似乎有文件Close()，可不写
	return flag;
}


// 创建第一人
BOOL CLoginDlg::CreateUser()
{
	CFile file;
	if (!file.Open(ADMIN_DATA, CFile::modeCreate | CFile::modeWrite))
		return FALSE;

	file.Write(&m_firstAdmin, sizeof(m_firstAdmin));
	file.Close();
	return TRUE;
}
