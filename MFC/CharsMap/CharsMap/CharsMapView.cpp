
// CharsMapView.cpp: CCharsMapView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CharsMap.h"
#endif

#include "CharsMapDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "CharsMapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharsMapView

IMPLEMENT_DYNCREATE(CCharsMapView, CRichEditView)

BEGIN_MESSAGE_MAP(CCharsMapView, CRichEditView)
	ON_WM_DESTROY()
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCharsMapView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BTN_CIPHER, &CCharsMapView::OnBtnCipher)
	ON_UPDATE_COMMAND_UI(ID_BTN_CIPHER, &CCharsMapView::OnUpdateBtnCipher)
	ON_COMMAND(ID_BTN_TOCIPHER, &CCharsMapView::OnBtnTocipher)
	ON_UPDATE_COMMAND_UI(ID_BTN_TOCIPHER, &CCharsMapView::OnUpdateBtnTocipher)
	ON_COMMAND(ID_BTN_TOPLAIN_UPPER, &CCharsMapView::OnBtnToplainUpper)
	ON_UPDATE_COMMAND_UI(ID_BTN_TOPLAIN_UPPER, &CCharsMapView::OnUpdateBtnToplainUpper)
	ON_COMMAND(ID_BTN_TOPLAIN_LOWER, &CCharsMapView::OnBtnToplainLower)
	ON_UPDATE_COMMAND_UI(ID_BTN_TOPLAIN_LOWER, &CCharsMapView::OnUpdateBtnToplainLower)
	ON_COMMAND(ID_BTN_SEAL, &CCharsMapView::OnBtnSeal)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEAL, &CCharsMapView::OnUpdateBtnSeal)
END_MESSAGE_MAP()

// CCharsMapView 构造/析构

CCharsMapView::CCharsMapView() noexcept : m_richedit(GetRichEditCtrl())
{
	// TODO: 在此处添加构造代码

}

CCharsMapView::~CCharsMapView()
{
}

BOOL CCharsMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CRichEditView::PreCreateWindow(cs);
}

void CCharsMapView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// 设置打印边距(720 缇 = 1/2 英寸)
	SetMargins(CRect(720, 720, 720, 720));
}


// CCharsMapView 打印


void CCharsMapView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCharsMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}


void CCharsMapView::OnDestroy()
{
	// 析构时停用此项；这在
	// 使用拆分器视图时非常重要 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CRichEditView::OnDestroy();
}


void CCharsMapView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCharsMapView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCharsMapView 诊断

#ifdef _DEBUG
void CCharsMapView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CCharsMapView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CCharsMapDoc* CCharsMapView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCharsMapDoc)));
	return (CCharsMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CCharsMapView 消息处理程序



// 密文
void CCharsMapView::OnBtnCipher()
{
	// 模态对话框
	//CCharsMapDlg charsmapDlg;
	//charsmapDlg.DoModal();

	// 创建非模态单例对话框
	if (!m_charsdlg.GetSafeHwnd())
		m_charsdlg.Create(IDD_CHARSMAP);
	m_charsdlg.ShowWindow(SW_SHOW);
}


void CCharsMapView::OnUpdateBtnCipher(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

// 转为密文，以大写字母输入
void CCharsMapView::OnBtnTocipher()
{
	CString text = m_richedit.GetSelText();		//选中的内容
	CString str;								//转换后的文本
	str.Empty();
	int len = text.GetLength();
	wchar_t plain, cipher;						//明文，密文
	CString tmp;
	for (int index = 0; index < len; index++)
	{
		tmp.Empty();

		plain = text.GetAt(index);
		switch (plain)
		{
		case _T(' '):
		case _T('\r'):
			str += plain;
			continue;
		default:
			break;
		}
		cipher = plain - L'A';
		tmp.Format(_T("%wc"), START_ALPHA + cipher + 1);
		str += tmp;
	}

	int length = m_richedit.GetWindowTextLength();
	m_richedit.SetSel(length, -1);
	m_richedit.ReplaceSel(_T("\r\n") + str);

}


void CCharsMapView::OnUpdateBtnTocipher(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

// Upper-case 大写字母，Lower-case 小写字母
// 转为明文大写
void CCharsMapView::OnBtnToplainUpper()
{
	CString text = m_richedit.GetSelText();		//选中的内容
	CString strUpper;							//转换后的文本，大写
	strUpper.Empty();
	int len = text.GetLength();
	wchar_t cipher, plain;						//密文，明文
	CString tmp;
	for (int index = 0; index < len; index++)
	{
		tmp.Empty();

		cipher = text.GetAt(index);
		switch (cipher)
		{
		case _T(' '):
		case _T('\r'):
			strUpper += cipher;
			continue;
		default:
			break;
		}
		plain = cipher - START_ALPHA;
		tmp.Format(_T("%wc"), L'A' + plain - 1);
		strUpper += tmp;
	}

	int length = m_richedit.GetWindowTextLength();
	m_richedit.SetSel(length, -1);
	m_richedit.ReplaceSel(_T("\r\n") + strUpper);

}


void CCharsMapView::OnUpdateBtnToplainUpper(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

// 转为明文小写
void CCharsMapView::OnBtnToplainLower()
{
	CString text = m_richedit.GetSelText();		//选中的内容
	CString strLower;							//转换后的文本，小写
	strLower.Empty();
	int len = text.GetLength();
	wchar_t cipher, plain;						//密文，明文
	CString tmp;
	for (int index = 0; index < len; index++)
	{
		tmp.Empty();

		cipher = text.GetAt(index);
		switch (cipher)
		{
		case _T(' '):
		case _T('\r'):
			strLower += cipher;
			continue;
		default:
			break;
		}
		plain = cipher - START_ALPHA;
		tmp.Format(_T("%wc"), L'a' + plain - 1);
		strLower += tmp;
	}

	int length = m_richedit.GetWindowTextLength();
	m_richedit.SetSel(length, -1);
	m_richedit.ReplaceSel(_T("\r\n") + strLower);

}


void CCharsMapView::OnUpdateBtnToplainLower(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CCharsMapView::OnBtnSeal()
{
	CSealDlg m_sealDlg;
	m_sealDlg.DoModal();
}


void CCharsMapView::OnUpdateBtnSeal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
