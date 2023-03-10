
// Worker.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Worker.h"
#include "WorkerDlg.h"
#include "CMainDlg.h"
#include "CAdminDlg.h"
#include "CLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// !CString结尾用NULL或nullptr，if(_T("")) or if(_T("\0")) 均为true.
// 数据更新：修改保存为新结构体运行程序加载后保存，再修改加载为新结构体运行即可。旧数据未使用字段需判断。
CString CWorkerApp::m_szWorker[WORKER_SIZE] = {
	_T("工号"), _T("姓名"), _T("性别") ,_T("薪资"), _T("入职日期") ,_T("学历"), _T("外语"), nullptr
};

CString CWorkerApp::m_szPrority[] = { _T("普通"), _T("高级"), nullptr };

LPCTSTR CWorkerApp::m_szSex[] = { _T("女"), _T("男"), _T("\0") };
CString CWorkerApp::m_szGraduate[] = { _T("高中"), _T("专科"), _T("本科") , _T("硕士") , _T("博士"), nullptr };
LPCTSTR CWorkerApp::m_szLanguage[] = { _T("英语 "), _T("日语 "), _T("韩语 "), _T("法语 "), _T("俄语 "), nullptr };
DWORD CWorkerApp::m_dwordLangs[] = {
	0x00000001,
	0x00000010,
	0x00000100,
	0x00001000,
	0x00010000
};


// CWorkerApp

BEGIN_MESSAGE_MAP(CWorkerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWorkerApp 构造

CWorkerApp::CWorkerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CWorkerApp 对象

CWorkerApp theApp;


// CWorkerApp 初始化

BOOL CWorkerApp::InitInstance()
{
	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("WorkerData"));

	CLoginDlg dlg;
	//CAdminDlg dlg;
	if (IDCANCEL == dlg.DoModal())
		goto OVER;

	while (true)
	{
		CMainDlg maindlg;
		//m_pMainWnd = &maindlg;
		INT_PTR nResponse = maindlg.DoModal();
		switch (nResponse)
		{
		case IDCANCEL:
			goto OVER;
		case IDC_BTN_RELOGIN:
		{
			CLoginDlg logindlg;
			if (IDCANCEL == logindlg.DoModal())
				goto OVER;
		}
		case IDC_BTN_INFO:
		{
			CWorkerDlg workerdlg;
			// 获取对话框对象以相互间传递数据：
			//方法1. m_pMainWnd = &maindlg;  (CWorkerDlg*)AfxGetMainWnd();
			//方法2. 定义类的指针作为成员变量（推荐使用）
			workerdlg.DoModal();
			break;
		}
		case IDC_BTN_ADMIN:
		{
			CAdminDlg admindlg;
			admindlg.DoModal();
			break;
		}
		default:
			break;
		}
	}
OVER:

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

