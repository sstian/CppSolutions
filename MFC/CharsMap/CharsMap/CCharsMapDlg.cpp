// CCharsMapDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CharsMap.h"
#include "CCharsMapDlg.h"
#include "afxdialogex.h"


// CCharsMapDlg 对话框

IMPLEMENT_DYNAMIC(CCharsMapDlg, CDialogEx)

CCharsMapDlg::CCharsMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARSMAP, pParent)
{
	//m_pmfcbtns.RemoveAll();
	m_alphas.RemoveAll();
	m_ids.RemoveAll();
	m_mapidbtn.RemoveAll();


}

CCharsMapDlg::~CCharsMapDlg()
{
	//m_pmfcbtns.RemoveAll();
	m_alphas.RemoveAll();
	m_mapidbtn.RemoveAll();
	m_ids.RemoveAll();
}

void CCharsMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBTN_A, m_mfcbtnA);
	DDX_Control(pDX, IDC_MFCBTN_B, m_mfcbtnB);
	DDX_Control(pDX, IDC_MFCBTN_C, m_mfcbtnC);
	DDX_Control(pDX, IDC_MFCBTN_D, m_mfcbtnD);
	DDX_Control(pDX, IDC_MFCBTN_E, m_mfcbtnE);
	DDX_Control(pDX, IDC_MFCBTN_F, m_mfcbtnF);
	DDX_Control(pDX, IDC_MFCBTN_G, m_mfcbtnG);
	DDX_Control(pDX, IDC_MFCBTN_H, m_mfcbtnH);
	DDX_Control(pDX, IDC_MFCBTN_I, m_mfcbtnI);
	DDX_Control(pDX, IDC_MFCBTN_J, m_mfcbtnJ);
	DDX_Control(pDX, IDC_MFCBTN_K, m_mfcbtnK);
	DDX_Control(pDX, IDC_MFCBTN_L, m_mfcbtnL);
	DDX_Control(pDX, IDC_MFCBTN_M, m_mfcbtnM);
	DDX_Control(pDX, IDC_MFCBTN_N, m_mfcbtnN);
	DDX_Control(pDX, IDC_MFCBTN_O, m_mfcbtnO);
	DDX_Control(pDX, IDC_MFCBTN_P, m_mfcbtnP);
	DDX_Control(pDX, IDC_MFCBTN_Q, m_mfcbtnQ);
	DDX_Control(pDX, IDC_MFCBTN_R, m_mfcbtnR);
	DDX_Control(pDX, IDC_MFCBTN_S, m_mfcbtnS);
	DDX_Control(pDX, IDC_MFCBTN_T, m_mfcbtnT);
	DDX_Control(pDX, IDC_MFCBTN_U, m_mfcbtnU);
	DDX_Control(pDX, IDC_MFCBTN_V, m_mfcbtnV);
	DDX_Control(pDX, IDC_MFCBTN_W, m_mfcbtnW);
	DDX_Control(pDX, IDC_MFCBTN_X, m_mfcbtnX);
	DDX_Control(pDX, IDC_MFCBTN_Y, m_mfcbtnY);
	DDX_Control(pDX, IDC_MFCBTN_Z, m_mfcbtnZ);
	DDX_Control(pDX, IDC_MFCBTN_SPACE, m_mfcbtnSpace);
	DDX_Control(pDX, IDC_MFCBTN_ENTER, m_mfcbtnEnter);
}


BEGIN_MESSAGE_MAP(CCharsMapDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_MFCBTN_A, &CCharsMapDlg::OnBnClickedMfcbtnA)
//	ON_BN_SETFOCUS(IDC_MFCBTN_A, &CCharsMapDlg::OnSetfocusMfcbtnA)
//	ON_BN_KILLFOCUS(IDC_MFCBTN_A, &CCharsMapDlg::OnKillfocusMfcbtnA)
	ON_BN_CLICKED(IDC_MFCBTN_B, &CCharsMapDlg::OnBnClickedMfcbtnB)
	ON_BN_CLICKED(IDC_MFCBTN_C, &CCharsMapDlg::OnBnClickedMfcbtnC)
	ON_BN_CLICKED(IDC_MFCBTN_D, &CCharsMapDlg::OnBnClickedMfcbtnD)
	ON_BN_CLICKED(IDC_MFCBTN_E, &CCharsMapDlg::OnBnClickedMfcbtnE)
	ON_BN_CLICKED(IDC_MFCBTN_F, &CCharsMapDlg::OnBnClickedMfcbtnF)
	ON_BN_CLICKED(IDC_MFCBTN_G, &CCharsMapDlg::OnBnClickedMfcbtnG)
	ON_BN_CLICKED(IDC_MFCBTN_H, &CCharsMapDlg::OnBnClickedMfcbtnH)
	ON_BN_CLICKED(IDC_MFCBTN_I, &CCharsMapDlg::OnBnClickedMfcbtnI)
	ON_BN_CLICKED(IDC_MFCBTN_J, &CCharsMapDlg::OnBnClickedMfcbtnJ)
	ON_BN_CLICKED(IDC_MFCBTN_K, &CCharsMapDlg::OnBnClickedMfcbtnK)
	ON_BN_CLICKED(IDC_MFCBTN_L, &CCharsMapDlg::OnBnClickedMfcbtnL)
	ON_BN_CLICKED(IDC_MFCBTN_M, &CCharsMapDlg::OnBnClickedMfcbtnM)
	ON_BN_CLICKED(IDC_MFCBTN_N, &CCharsMapDlg::OnBnClickedMfcbtnN)
	ON_BN_CLICKED(IDC_MFCBTN_O, &CCharsMapDlg::OnBnClickedMfcbtnO)
	ON_BN_CLICKED(IDC_MFCBTN_P, &CCharsMapDlg::OnBnClickedMfcbtnP)
	ON_BN_CLICKED(IDC_MFCBTN_Q, &CCharsMapDlg::OnBnClickedMfcbtnQ)
	ON_BN_CLICKED(IDC_MFCBTN_R, &CCharsMapDlg::OnBnClickedMfcbtnR)
	ON_BN_CLICKED(IDC_MFCBTN_S, &CCharsMapDlg::OnBnClickedMfcbtnS)
	ON_BN_CLICKED(IDC_MFCBTN_T, &CCharsMapDlg::OnBnClickedMfcbtnT)
	ON_BN_CLICKED(IDC_MFCBTN_U, &CCharsMapDlg::OnBnClickedMfcbtnU)
	ON_BN_CLICKED(IDC_MFCBTN_V, &CCharsMapDlg::OnBnClickedMfcbtnV)
	ON_BN_CLICKED(IDC_MFCBTN_W, &CCharsMapDlg::OnBnClickedMfcbtnW)
	ON_BN_CLICKED(IDC_MFCBTN_X, &CCharsMapDlg::OnBnClickedMfcbtnX)
	ON_BN_CLICKED(IDC_MFCBTN_Y, &CCharsMapDlg::OnBnClickedMfcbtnY)
	ON_BN_CLICKED(IDC_MFCBTN_Z, &CCharsMapDlg::OnBnClickedMfcbtnZ)
	ON_BN_CLICKED(IDC_MFCBTN_SPACE, &CCharsMapDlg::OnBnClickedMfcbtnSpace)
	ON_BN_CLICKED(IDC_MFCBTN_ENTER, &CCharsMapDlg::OnBnClickedMfcbtnEnter)
END_MESSAGE_MAP()


// CCharsMapDlg 消息处理程序

BOOL CCharsMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 参数初始化
	//m_pmfcbtns.Add(&m_mfcbtnA);
	//m_pmfcbtns.Add(&m_mfcbtnB);
	//m_pmfcbtns.Add(&m_mfcbtnC);
	//m_pmfcbtns.Add(&m_mfcbtnD);
	//m_pmfcbtns.Add(&m_mfcbtnE);
	//m_pmfcbtns.Add(&m_mfcbtnF);
	//m_pmfcbtns.Add(&m_mfcbtnG);
	//m_pmfcbtns.Add(&m_mfcbtnH);
	//m_pmfcbtns.Add(&m_mfcbtnI);

	// 存储控件IDs
	m_ids.Add(IDC_MFCBTN_SPACE);
	m_ids.Add(IDC_MFCBTN_A);
	m_ids.Add(IDC_MFCBTN_B);
	m_ids.Add(IDC_MFCBTN_C);
	m_ids.Add(IDC_MFCBTN_D);
	m_ids.Add(IDC_MFCBTN_E);
	m_ids.Add(IDC_MFCBTN_F);
	m_ids.Add(IDC_MFCBTN_G);
	m_ids.Add(IDC_MFCBTN_H);
	m_ids.Add(IDC_MFCBTN_I);
	m_ids.Add(IDC_MFCBTN_J);
	m_ids.Add(IDC_MFCBTN_K);
	m_ids.Add(IDC_MFCBTN_L);
	m_ids.Add(IDC_MFCBTN_M);
	m_ids.Add(IDC_MFCBTN_N);
	m_ids.Add(IDC_MFCBTN_O);
	m_ids.Add(IDC_MFCBTN_P);
	m_ids.Add(IDC_MFCBTN_Q);
	m_ids.Add(IDC_MFCBTN_R);
	m_ids.Add(IDC_MFCBTN_S);
	m_ids.Add(IDC_MFCBTN_T);
	m_ids.Add(IDC_MFCBTN_U);
	m_ids.Add(IDC_MFCBTN_V);
	m_ids.Add(IDC_MFCBTN_W);
	m_ids.Add(IDC_MFCBTN_X);
	m_ids.Add(IDC_MFCBTN_Y);
	m_ids.Add(IDC_MFCBTN_Z);
	m_ids.Add(IDC_MFCBTN_ENTER);


	// 映射控件ID与关联变量
	m_mapidbtn.SetAt(IDC_MFCBTN_A, &m_mfcbtnA);
	m_mapidbtn.SetAt(IDC_MFCBTN_B, &m_mfcbtnB);
	m_mapidbtn.SetAt(IDC_MFCBTN_C, &m_mfcbtnC);
	m_mapidbtn.SetAt(IDC_MFCBTN_D, &m_mfcbtnD);
	m_mapidbtn.SetAt(IDC_MFCBTN_E, &m_mfcbtnE);
	m_mapidbtn.SetAt(IDC_MFCBTN_F, &m_mfcbtnF);
	m_mapidbtn.SetAt(IDC_MFCBTN_G, &m_mfcbtnG);
	m_mapidbtn.SetAt(IDC_MFCBTN_H, &m_mfcbtnH);
	m_mapidbtn.SetAt(IDC_MFCBTN_I, &m_mfcbtnI);
	m_mapidbtn.SetAt(IDC_MFCBTN_J, &m_mfcbtnJ);
	m_mapidbtn.SetAt(IDC_MFCBTN_K, &m_mfcbtnK);
	m_mapidbtn.SetAt(IDC_MFCBTN_L, &m_mfcbtnL);
	m_mapidbtn.SetAt(IDC_MFCBTN_M, &m_mfcbtnM);
	m_mapidbtn.SetAt(IDC_MFCBTN_N, &m_mfcbtnN);
	m_mapidbtn.SetAt(IDC_MFCBTN_O, &m_mfcbtnO);
	m_mapidbtn.SetAt(IDC_MFCBTN_P, &m_mfcbtnP);
	m_mapidbtn.SetAt(IDC_MFCBTN_Q, &m_mfcbtnQ);
	m_mapidbtn.SetAt(IDC_MFCBTN_R, &m_mfcbtnR);
	m_mapidbtn.SetAt(IDC_MFCBTN_S, &m_mfcbtnS);
	m_mapidbtn.SetAt(IDC_MFCBTN_T, &m_mfcbtnT);
	m_mapidbtn.SetAt(IDC_MFCBTN_U, &m_mfcbtnU);
	m_mapidbtn.SetAt(IDC_MFCBTN_V, &m_mfcbtnV);
	m_mapidbtn.SetAt(IDC_MFCBTN_W, &m_mfcbtnW);
	m_mapidbtn.SetAt(IDC_MFCBTN_X, &m_mfcbtnX);
	m_mapidbtn.SetAt(IDC_MFCBTN_Y, &m_mfcbtnY);
	m_mapidbtn.SetAt(IDC_MFCBTN_Z, &m_mfcbtnZ);

	// 设置控件文本字体
	CFont* pFont = GetFont();
	LOGFONT lg;
	pFont->GetLogFont(&lg);
	_tcscpy_s(lg.lfFaceName, _T("等线"));
	//lg.lfWeight = 10;
	//lg.lfWidth = 50;
	lg.lfHeight = 30;
	m_font.CreateFontIndirect(&lg);

	//m_mfcbtnA.SetFont(&m_font);
	//m_mfcbtnA.m_bDrawFocus = FALSE;
	
	//int size = (int)m_pmfcbtns.GetSize();
	//for (int index = 0; index < size; index++)
	//{
	//	m_pmfcbtns.GetAt(index)->SetFont(&m_font);
	//	m_pmfcbtns.GetAt(index)->m_bDrawFocus = FALSE;
	//}

	int id = 0;
	for (int index = 1; index <= 26; index++)
	{
		id = m_ids.GetAt(index);
		m_mapidbtn[id]->SetFont(&m_font);
		m_mapidbtn[id]->m_bDrawFocus = FALSE;
	}
	m_mfcbtnSpace.SetFont(&m_font);
	m_mfcbtnEnter.SetFont(&m_font);

	// 转换Unicode编码到字符存储
	wchar_t wc = 0;
	CString str;
	for (int index = START_ALPHA; index <= START_ALPHA + 27; index++)
	{		
		str.Empty();
		wc = index;
		str.Format(_T("%wc"), wc);
		m_alphas.Add(str);
	}
	
	// 获得视图View
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CCharsMapView* pView = (CCharsMapView*)pFrame->GetActiveView();
	//CRichEditCtrl& rich = pView->m_richedit;
	m_prich  = &pView->m_richedit;



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CCharsMapDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 绘制图形
	// 图形2
	CRect rect;
	GetDlgItem(IDC_PATTERN20)->GetWindowRect(rect);
	ScreenToClient(rect);
	int width = rect.Width();		//146
	int height = rect.Height();		//146
	TRACE(_T("rect: width() = %d, height() = %d\n"), width, height);

	// 图形3
	CRect rect3;
	GetDlgItem(IDC_PATTERN30)->GetWindowRect(rect3);
	ScreenToClient(rect3);
	int width3 = rect3.Width();			//90
	int height3 = rect3.Height();		//89
	TRACE(_T("rect3: width() = %d, height() = %d\n"), width3, height3);

	CPen pen(PS_SOLID, 1, RGB(160, 160, 160));	// Etched Color
	CPen pen2(PS_SOLID, 1, RGB(255, 255, 255));	// White Color

	for (int i = 1; i >= 0; i--)
	{
		// 先画白线，再画刻蚀线条
		0 == i ? dc.SelectObject(pen) : dc.SelectObject(pen2);

		// 图形2
		dc.MoveTo(rect.TopLeft() + CPoint(0, -i));		// /* \ */
		dc.LineTo(rect.BottomRight() + CPoint(0, -i));
		dc.MoveTo(rect.right, rect.top + i);			// /* / */
		dc.LineTo(rect.left, rect.bottom + i);
		int centerHeight = rect.top + rect.Height() / 2;
		int centerWidth = rect.left + rect.Width() / 2;
		dc.MoveTo(rect.left, centerHeight + i);			// /* - */
		dc.LineTo(rect.right, centerHeight + i);
		dc.MoveTo(centerWidth + i, rect.top);			// /* | */
		dc.LineTo(centerWidth + i, rect.bottom);


		// 图形3
		CArray<CPoint> aps;
		aps.Add(rect3.TopLeft() + CPoint(i, 0));
		aps.Add(CPoint(rect3.left + i, rect3.top - width3));
		aps.Add(CPoint(rect3.right, rect3.top + i));
		aps.Add(CPoint(rect3.right + height3, rect3.top + i));
		aps.Add(rect3.BottomRight() + CPoint(i, 0));
		aps.Add(CPoint(rect3.right + i, rect3.bottom + width3));
		aps.Add(CPoint(rect3.left + i, rect3.bottom));
		aps.Add(CPoint(rect3.left - height3, rect3.bottom + i));
		aps.Add(rect3.TopLeft() + CPoint(0, i));

		CBrush brush(GetSysColor(COLOR_3DFACE));
		dc.SelectObject(brush);
		CRect rt3 = rect3;
		rt3.OffsetRect(i, 0);
		dc.Rectangle(rt3);
		int count = (int)aps.GetCount();
		for (int index = 0; index < count - 2; index += 2)
		{
			CPoint pts[3] = { aps[index], aps[index + 1], aps[index + 2] };
			dc.MoveTo(pts[0]);
			dc.PolylineTo(pts, 3);
		}
		dc.MoveTo(aps[0]);
		dc.LineTo(aps[4]);
		dc.MoveTo(aps[2]);
		dc.LineTo(aps[6]);


	}

	//CPen pen2(PS_SOLID, 1, RGB(255, 255, 255));	// White Color
	//dc.SelectObject(pen2);
	//dc.MoveTo(rect.TopLeft() + CPoint(0, -1));
	//dc.LineTo(rect.BottomRight() + CPoint(0, -1));
	//dc.MoveTo(rect.right + 0, rect.top + 1);
	//dc.LineTo(rect.left + 0, rect.bottom + 1);
	//dc.MoveTo(rect.left + 0, centerHeight + 1);
	//dc.LineTo(rect.right + 0, centerHeight + 1);
	//dc.MoveTo(centerWidth + 1, rect.top + 0);
	//dc.LineTo(centerWidth + 1, rect.bottom + 0);


	pen.DeleteObject();
	pen2.DeleteObject();

}

void CCharsMapDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent - TIMER_CODE)
	{
	case CCharsMapDlg::A:
		m_mfcbtnA.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnA.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + A);
		break;
	case CCharsMapDlg::B:
		m_mfcbtnB.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnB.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + B);
		break;
	case CCharsMapDlg::C:
		m_mfcbtnC.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnC.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + C);
		break;
	case CCharsMapDlg::D:
		m_mfcbtnD.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnD.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + D);
		break;
	case CCharsMapDlg::E:
		m_mfcbtnE.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnE.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + E);
		break;
	case CCharsMapDlg::F:
		m_mfcbtnF.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnF.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + F);
		break;
	case CCharsMapDlg::G:
		m_mfcbtnG.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnG.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + G);
		break;
	case CCharsMapDlg::H:
		m_mfcbtnH.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnH.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + H);
		break;
	case CCharsMapDlg::I:
		m_mfcbtnI.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnI.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + I);
		break;
	case CCharsMapDlg::J:
		m_mfcbtnJ.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnJ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + J);
		break;
	case CCharsMapDlg::K:
		m_mfcbtnK.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnK.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + K);
		break;
	case CCharsMapDlg::L:
		m_mfcbtnL.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnL.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + L);
		break;
	case CCharsMapDlg::M:
		m_mfcbtnM.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnM.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + M);
		break;
	case CCharsMapDlg::N:
		m_mfcbtnN.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnN.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + N);
		break;
	case CCharsMapDlg::O:
		m_mfcbtnO.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnO.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + O);
		break;
	case CCharsMapDlg::P:
		m_mfcbtnP.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnP.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + P);
		break;
	case CCharsMapDlg::Q:
		m_mfcbtnQ.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnQ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + Q);
		break;
	case CCharsMapDlg::R:
		m_mfcbtnR.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnR.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + R);
		break;
	case CCharsMapDlg::S:
		m_mfcbtnS.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnS.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + S);
		break;
	case CCharsMapDlg::T:
		m_mfcbtnT.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnT.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + T);
		break;
	case CCharsMapDlg::U:
		m_mfcbtnU.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnU.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + U);
		break;
	case CCharsMapDlg::V:
		m_mfcbtnV.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnV.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + V);
		break;
	case CCharsMapDlg::W:
		m_mfcbtnW.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnW.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + W);
		break;
	case CCharsMapDlg::X:
		m_mfcbtnX.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnX.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + X);
		break;
	case CCharsMapDlg::Y:
		m_mfcbtnY.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnY.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + Y);
		break;
	case CCharsMapDlg::Z:
		m_mfcbtnZ.SetTextColor(RGB(0, 0, 0));
		m_mfcbtnZ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
		KillTimer(TIMER_CODE + Z);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CCharsMapDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//switch (pWnd->GetDlgCtrlID())
	//{
	//case IDC_MFCBTN_A:
	//	m_mfcbtnA.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	//	break;
	//case IDC_MFCBTN_B:
	//	m_mfcbtnB.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	//	break;
	//case IDC_MFCBTN_C:
	//	m_mfcbtnC.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	//	break;

	//default:
	//	int size = (int)m_pmfcbtns.GetSize();
	//	for (int index = 0; index < size; index++)
	//		m_pmfcbtns.GetAt(index)->SetFaceColor(GetSysColor(COLOR_3DFACE));
	//	break;
	//}
	CMFCButton* pmfcbtn = nullptr;
	int id = pWnd->GetDlgCtrlID();
	if(m_mapidbtn.Lookup(id, pmfcbtn))
		m_mapidbtn[id]->SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	else
	{
		for (int index = 1; index <= 26; index++)
			m_mapidbtn[m_ids.GetAt(index)]->SetFaceColor(GetSysColor(COLOR_3DFACE));
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CCharsMapDlg::OnBnClickedMfcbtnA()
{
	//m_prich->SetFocus();

	m_mfcbtnA.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnA.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + A, 100, nullptr);

	//CCharsMapView* pView = (CCharsMapView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	//CRichEditCtrl& rich = pView->m_richedit;
	//int length = rich.GetWindowTextLength();
	//rich.SetSel(length, -1);
	//CString str = m_alphas[A];
	//rich.ReplaceSel(str);

	//int length = m_prich->GetWindowTextLength();
	//m_prich->SetSel(length, -1);
	//如果未选中，start = end = WindowTextLength，在光标处插入
	long start, end;
	m_prich->GetSel(start, end);	
	m_prich->SetSel(start, end);
	CString str = m_alphas[A];
	m_prich->ReplaceSel(str);

}


//void CCharsMapDlg::OnSetfocusMfcbtnA()
//{
//	m_mfcbtnA.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
//}


//void CCharsMapDlg::OnKillfocusMfcbtnA()
//{
//	m_mfcbtnA.SetFaceColor(GetSysColor(COLOR_BTNFACE));
//}




void CCharsMapDlg::OnBnClickedMfcbtnB()
{
	m_mfcbtnB.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnB.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + B, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[B];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnC()
{
	m_mfcbtnC.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnC.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + C, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[C];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnD()
{
	m_mfcbtnD.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnD.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + D, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[D];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnE()
{
	m_mfcbtnE.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnE.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + E, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[E];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnF()
{
	m_mfcbtnF.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnF.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + F, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[F];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnG()
{
	m_mfcbtnG.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnG.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + G, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[G];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnH()
{
	m_mfcbtnH.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnH.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + H, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[H];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnI()
{
	m_mfcbtnI.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnI.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + I, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[I];
	m_prich->ReplaceSel(str);

}




void CCharsMapDlg::OnBnClickedMfcbtnJ()
{
	m_mfcbtnJ.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnJ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + J, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[J];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnK()
{
	m_mfcbtnK.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnK.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + K, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[K];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnL()
{
	m_mfcbtnL.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnL.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + L, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[L];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnM()
{
	m_mfcbtnM.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnM.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + M, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[M];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnN()
{
	m_mfcbtnN.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnN.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + N, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[N];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnO()
{
	m_mfcbtnO.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnO.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + O, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[O];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnP()
{
	m_mfcbtnP.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnP.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + P, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[P];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnQ()
{
	m_mfcbtnQ.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnQ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + Q, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[Q];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnR()
{
	m_mfcbtnR.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnR.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + R, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[R];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnS()
{
	m_mfcbtnS.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnS.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + S, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[S];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnT()
{
	m_mfcbtnT.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnT.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + T, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[T];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnU()
{
	m_mfcbtnU.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnU.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + U, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[U];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnV()
{
	m_mfcbtnV.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnV.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + V, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[V];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnW()
{
	m_mfcbtnW.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnW.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + W, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[W];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnX()
{
	m_mfcbtnX.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnX.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + X, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[X];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnY()
{
	m_mfcbtnY.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnY.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + Y, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[Y];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnZ()
{
	m_mfcbtnZ.SetTextColor(RGB(255, 0, 0));
	m_mfcbtnZ.SetFaceColor(GetSysColor(COLOR_INACTIVECAPTION));
	SetTimer(TIMER_CODE + Z, 100, nullptr);

	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = m_alphas[Z];
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnSpace()
{
	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = _T(" ");
	m_prich->ReplaceSel(str);

}


void CCharsMapDlg::OnBnClickedMfcbtnEnter()
{
	long start, end;
	m_prich->GetSel(start, end);
	m_prich->SetSel(start, end);
	CString str = _T("\r\n");
	m_prich->ReplaceSel(str);

}
