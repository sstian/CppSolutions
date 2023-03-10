
// GPADlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GPA.h"
#include "GPADlg.h"
#include "CAboutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CGPADlg 对话框



CGPADlg::CGPADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ids.RemoveAll();
	m_ids.Add(IDC_EDIT_NAME);
	m_ids.Add(IDC_EDIT_SCORE);
	m_ids.Add(IDC_EDIT_GRADE);

	m_modified = FALSE;
}

CGPADlg::~CGPADlg()
{
	m_ids.RemoveAll();
}

void CGPADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GPA, m_list);
}

BEGIN_MESSAGE_MAP(CGPADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_ADD, &CGPADlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(ID_BTN_DELETE, &CGPADlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(ID_BTN_MODIFY, &CGPADlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(ID_BTN_LOAD, &CGPADlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(ID_BTN_SAVE, &CGPADlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CALC, &CGPADlg::OnBnClickedBtnCalc)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CGPADlg 消息处理程序

BOOL CGPADlg::OnInitDialog()
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

	m_list.InsertColumn(0, _T("课程名"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, _T("课程成绩"), LVCFMT_LEFT,180);
	m_list.InsertColumn(2, _T("学分"), LVCFMT_LEFT, 170);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGPADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGPADlg::OnPaint()
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
HCURSOR CGPADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGPADlg::OnBnClickedBtnAdd()
{
	CString cstr;
	int item = m_list.GetItemCount();
	int size = (int)m_ids.GetSize();
	for (int i = 0; i < size; i++)
	{
		GetDlgItemText(m_ids.GetAt(i), cstr);
		(0 == i) ? m_list.InsertItem(item, cstr) : m_list.SetItemText(item, i, cstr);
		
		m_modified = TRUE;
	}
}


void CGPADlg::OnBnClickedBtnDelete()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox(_T("至少选择一行！"));
		return;
	}
	POSITION pos = nullptr;
	while (m_list.GetFirstSelectedItemPosition())
	{
		int item = m_list.GetNextSelectedItem(pos);
		m_list.DeleteItem(item);

		m_modified = TRUE;
	}
}


void CGPADlg::OnBnClickedBtnModify()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox(_T("至少选择一行！"));
		return;
	}
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	while (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		CString cstr;
		int size = (int)m_ids.GetSize();
		for (int i = 0; i < size; i++)
		{
			GetDlgItemText(m_ids.GetAt(i), cstr);
			m_list.SetItemText(item, i, cstr);
		}

		m_modified = TRUE;
	}
}


void CGPADlg::OnBnClickedBtnLoad()
{
	CFile file;
	if (!file.Open(GRADE_DATA, CFile::modeRead))
	{
		this->OnBnClickedBtnSave();
		if (!file.Open(GRADE_DATA, CFile::modeRead))
			return;
	}
	SGrade grade;
	CString cstr;
	for (int item = 0; sizeof(grade) == file.Read(&grade, sizeof(grade)); item++)
	{
		m_list.InsertItem(item, grade.name);
		cstr.Format(_T("%f"), grade.score);
		m_list.SetItemText(item, 1, cstr);
		cstr.Format(_T("%f"), grade.grade);
		m_list.SetItemText(item, 2, cstr);
	}
	file.Close();
}


void CGPADlg::OnBnClickedBtnSave()
{
	CFile file;
	if (!file.Open(GRADE_DATA, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("保存文件时出错！"));
		return;
	}
	SGrade grade;
	CString cstr;
	int count = m_list.GetItemCount();
	for (int item = 0; item < count; item++)
	{
		m_list.GetItemText(item, 0, grade.name, sizeof(grade.name));
		grade.score = _tcstof(m_list.GetItemText(item, 1), nullptr);
		grade.grade = _tcstof(m_list.GetItemText(item, 2), nullptr);
		file.Write(&grade, sizeof(grade));
	}
	m_modified = FALSE;
	file.Close();
}


void CGPADlg::OnBnClickedBtnCalc()
{
	float score, point, grade;
	float sumPointXGrade = 0.0f, sumGrade = 0.0f;
	int count = m_list.GetItemCount();
	for (int item = 0; item < count; item++)
	{
		score = _tcstof(m_list.GetItemText(item, 1), nullptr);	//成绩
		grade = _tcstof(m_list.GetItemText(item, 2), nullptr);	//学分
		point = this->ScoreToPoint(score);
		
		sumPointXGrade += point * grade;
		sumGrade += grade;
	}
	float gpa = sumPointXGrade / sumGrade;
	
	CString strHint = _T("您的GPA = ");
	CString strGPA;
	strGPA.Format(_T("%f"), gpa);
	strHint += strGPA;
	AfxMessageBox(strHint);
}


void CGPADlg::OnClose()
{
	if (m_modified)
	{
		int id = AfxMessageBox(_T("要保存改动的结果吗？"), MB_YESNOCANCEL);
		switch (id)
		{
		case IDYES:
			this->OnBnClickedBtnSave();
			break;
		//case IDNO:
		//	break;
		case IDCANCEL:
			return;
		//default:
		//	break;
		}
	}
	EndDialog(IDCANCEL);
	//CDialogEx::OnClose();
}


void CGPADlg::OnOK()
{
	NextDlgCtrl();
	int id = GetFocus()->GetDlgCtrlID();
	if (ID_BTN_ADD == id || IDC_EDIT_NAME == id)
	{
		this->OnBnClickedBtnAdd();
		SetFocus();
	}

	//CDialogEx::OnOK();
}

float CGPADlg::ScoreToPoint(const float & score)
{
	float point = 0.0f;
	if (score >= 95 && score <= 100)
		point = 4.0f;
	else if (score >= 90 && score <= 94)
		point = 3.9f;
	else if (score >= 85 && score <= 89)
		point = 3.7f;
	else if (score >= 81 && score <= 84)
		point = 3.3f;
	else if (score >= 78 && score <= 80)
		point = 3.0f;
	else if (score >= 75 && score <= 77)
		point = 2.7f;
	else if (score >= 71 && score <= 74)
		point = 2.3f;
	else if (score >= 68 && score <= 70)
		point = 2.0;
	else if (score >= 64 && score <= 67)
		point = 1.7f;
	else if (score >= 60 && score <= 63)
		point = 1.0f;
	else 
		point = 0.0f;

	return point;
}

float CGPADlg::FiveDegreeToPoint(const CString & degree)
{
	float point = 0.0f;
	CString strDegree[6] = {
		_T("优"),_T("良"),_T("中"),_T("合格"),_T("不合格"),_T("\0")
	};

	if (degree == strDegree[0])
		point = 3.9f;
	else if (degree == strDegree[1])
		point = 3.3f;
	else if (degree == strDegree[2])
		point = 2.3f;
	else if (degree == strDegree[3])
		point = 1.0f;
	else if (degree == strDegree[4])
		point = 0.0f;

	return point;
}
