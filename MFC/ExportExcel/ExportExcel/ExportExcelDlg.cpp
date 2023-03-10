
// ExportExcelDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ExportExcel.h"
#include "ExportExcelDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "IllusionExcelFile.h"
#include "ExcelFields.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExportExcelDlg 对话框


IMPLEMENT_DYNAMIC(CExportExcelDlg, CDialogEx);

CExportExcelDlg::CExportExcelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPORTEXCEL_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CExportExcelDlg::~CExportExcelDlg()
{
	// 如果该对话框有自动化代理，则
	//  此对话框的返回指针为 null，所以它知道
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CExportExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExportExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CExportExcelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CExportExcelDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CExportExcelDlg 消息处理程序

BOOL CExportExcelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CExportExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExportExcelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExportExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CExportExcelDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CExportExcelDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CExportExcelDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CExportExcelDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CExportExcelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//定义一个Excel操作对象
	IllusionExcelFile excel;

	//初始化Excel相关工作
	bool bInit = excel.InitExcel();

	//打开Excel文件
	bool bRet = excel.OpenExcelFile(_T("InputData.xlsx"));

	//加载工作表：通过表序号
	CString strSheetName = excel.GetSheetName(1);
	//bool bLoad = excl.LoadSheet(strSheetName);	
	bool bLoad = excel.LoadSheet(strSheetName, true);	//预先加载

	//1.读操作
	///写入定义的类中，可以进行后续的数据处理分析操作。。。
	Puck puck[3];

	int nRow = excel.GetRowCount();
	int nCol = excel.GetColumnCount();
	for (int i = 2; i <= nRow; ++i)
	{
		CTime ctime_arrive, ctime_leave;

		for (int j = 1; j <= nCol; ++j)
		{
			CString strValue = excel.GetCellString(i, j);
			//AfxMessageBox(strValue);

			switch (j)
			{
			case 1:
				puck[i - 2].setPuckNumber(strValue);
				break;
			case 2:
				IllusionExcelFile::FormatDateTime(ctime_arrive, strValue, ExcelFormat::ExcelDate);
				break;
			case 3:
				IllusionExcelFile::FormatDateTime(ctime_arrive, strValue, ExcelFormat::ExcelTime);
				puck[i - 2].setArriveDateTime(ctime_arrive);
				break;
			case 4:
				puck[i - 2].setArriveFlight(strValue);
				break;
			case 5:
				puck[i - 2].setArriveType(strValue);
				break;
			case 6:
				puck[i - 2].setPlaneType(strValue);
				break;
			case 7:
				IllusionExcelFile::FormatDateTime(ctime_leave, strValue, ExcelFormat::ExcelDate);
				break;
			case 8:
				IllusionExcelFile::FormatDateTime(ctime_leave, strValue, ExcelFormat::ExcelTime);
				puck[i - 2].setLeaveDateTime(ctime_leave);
				break;
			case 9:
				puck[i - 2].setLeaveFlight(strValue);
				break;
			case 10:
				puck[i - 2].setLeaveType(strValue);
				break;
			case 11:
				puck[i - 2].setOnlineAriport(strValue);
				break;
			case 12:
				puck[i - 2].setDownlineAriport(strValue);
				break;

			default:
				break;
			}

			////合并日期时间两列为CTime
			//if (j == 2)
			//{
			//	IllusionExcelFile::FormatDateTime(ctime_arrive, strValue, ExcelFormat::ExcelDate);
			//	//AfxMessageBox(ctime.Format(_T("%Y/%m/%d %H:%M:%S")));
			//}
			//if (j == 3)
			//{
			//	IllusionExcelFile::FormatDateTime(ctime_arrive, strValue, ExcelFormat::ExcelTime);
			//	//AfxMessageBox(ctime.Format(_T("%Y/%m/%d %H:%M:%S")));
			//}

			//if (j == 7)
			//{
			//	IllusionExcelFile::FormatDateTime(ctime_leave, strValue, ExcelFormat::ExcelDate);
			//}
			//if (j == 8)
			//{
			//	IllusionExcelFile::FormatDateTime(ctime_leave, strValue, ExcelFormat::ExcelTime);
			//}
			
		}
	}
	AfxMessageBox(_T("Read OK!"));

	//关闭Excel文件
	excel.CloseExcelFile();

	CDialogEx::OnOK();
}


void CExportExcelDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	//定义一个Excel操作对象
	IllusionExcelFile excel;

	//初始化Excel相关工作
	bool bInit = excel.InitExcel();

	//打开Excel文件
	bool bRet = excel.OpenExcelFile(_T("InputData.xlsx"));

	//加载工作表：通过表名
	bool bLoad_Write = excel.LoadSheet(_T("data"));

	//2.写操作
	//产生随机数据（或者从内存中读取数据）。。。
	excel.SetCellString(1, 1, _T("id"));
	excel.SetCellString(1, 2, _T("rand_value"));
	for (int i = 1; i <= 10; i++)
	{
		//CString strCol_1;
		//strCol_1.Format(_T("%d"), i);
		//excel.SetCellString(i, 1, strCol_1);

		excel.SetCellInt(i + 1, 1, i);
		excel.SetCellInt(i + 1, 2, rand() % 100);
	}
	AfxMessageBox(_T("Write OK!"));

	//！保存文件数据，前提需要关闭Excel文件
	excel.SaveasXSLFile(_T("InputData.xlsx"));

	//关闭Excel文件
	excel.CloseExcelFile();

	CDialogEx::OnCancel();
}
