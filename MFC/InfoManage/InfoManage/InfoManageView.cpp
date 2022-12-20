
// InfoManageView.cpp: CInfoManageView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "InfoManage.h"
#endif

#include "InfoManageDoc.h"
#include "InfoManageView.h"
#include "CInfoDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInfoManageView

IMPLEMENT_DYNCREATE(CInfoManageView, CListView)

BEGIN_MESSAGE_MAP(CInfoManageView, CListView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_ADD, &CInfoManageView::OnEditAdd)
	ON_COMMAND(ID_EDIT_DEL, &CInfoManageView::OnEditDel)
	ON_COMMAND(ID_EDIT_MOD, &CInfoManageView::OnEditMod)
	ON_COMMAND(ID_FILE_OPEN, &CInfoManageView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CInfoManageView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CInfoManageView::OnFileSaveAs)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CInfoManageView::OnNMDblclk)
END_MESSAGE_MAP()

// CInfoManageView 构造/析构

CInfoManageView::CInfoManageView() noexcept : m_list(GetListCtrl())
{
	m_file = _T("");

}

CInfoManageView::~CInfoManageView()
{
}

BOOL CInfoManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}


void CInfoManageView::OnDraw(CDC* /*pDC*/)
{
	CInfoManageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CInfoManageView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// 初始化数据
	m_list.DeleteAllItems();
	for(int i = 2; i >= 0; i--)
		m_list.DeleteColumn(i);

	m_list.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("工号"), 0, 200);
	m_list.InsertColumn(1, _T("姓名"), 0, 200);
	m_list.InsertColumn(2, _T("入职日期"), 0, 200);

	//m_doc.AddView(this);	//添加View
}


// CInfoManageView 打印

BOOL CInfoManageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CInfoManageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CInfoManageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CInfoManageView 诊断

#ifdef _DEBUG
void CInfoManageView::AssertValid() const
{
	CListView::AssertValid();
}

void CInfoManageView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CInfoManageDoc* CInfoManageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInfoManageDoc)));
	return (CInfoManageDoc*)m_pDocument;
}
#endif //_DEBUG


// CInfoManageView 消息处理程序

//BOOL CInfoManageView::CheckExit()
//{
//	if (m_doc.IsModified())
//	{
//		CString str = m_doc.GetTitle();
//		if (str.IsEmpty())
//			str = _T("无标题.dat");
//		str = _T("文件 ") + str + _T(" 已经更改！\n是否保存？");
//		int result = AfxMessageBox(str, MB_YESNOCANCEL);
//		switch (result)
//		{
//		case IDYES:
//			//this->OnFileSave();
//			return TRUE;
//		//case IDNO:
//		//	break;
//		case IDCANCEL:
//			return FALSE;
//		}
//	}
//	return TRUE;
//}

// 编辑 | 添加...
void CInfoManageView::OnEditAdd()
{
	CInfoDlg infoDlg;
	if (IDCANCEL == infoDlg.DoModal())
		return;

	UpdateData(TRUE);
	int item = m_list.GetItemCount();	
	m_list.InsertItem(item, infoDlg.m_number);
	m_list.SetItemText(item, 1, infoDlg.m_name);
	m_list.SetItemText(item, 2, infoDlg.m_datetime.Format(_T("%Y-%m-%d")));

	//m_doc.SetModifiedFlag();
	GetDocument()->SetModifiedFlag();
}

// 编辑 | 删除
void CInfoManageView::OnEditDel()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行！"));
		return;
	}
	POSITION pos = nullptr;
	while (m_list.GetFirstSelectedItemPosition())
	{
		int item = m_list.GetNextSelectedItem(pos);
		m_list.DeleteItem(item);

		//m_doc.SetModifiedFlag();
		GetDocument()->SetModifiedFlag();
	}
}

// 编辑 | 修改...
void CInfoManageView::OnEditMod()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行！"));
		return;
	}
	int item = m_list.GetSelectionMark();

	CInfoDlg infoDlg;
	infoDlg.m_title = _T("修改数据");
	infoDlg.m_number = m_list.GetItemText(item, 0);
	infoDlg.m_name = m_list.GetItemText(item, 1);
	infoDlg.m_datetime.ParseDateTime(m_list.GetItemText(item, 2));
	UpdateData(FALSE);

	if (IDCANCEL == infoDlg.DoModal())
		return;

	UpdateData(TRUE);
	m_list.SetItemText(item, 0, infoDlg.m_number);
	m_list.SetItemText(item, 1, infoDlg.m_name);
	m_list.SetItemText(item, 2, infoDlg.m_datetime.Format());

	//m_doc.SetModifiedFlag();
	GetDocument()->SetModifiedFlag();

}

 //文件 | 打开...
void CInfoManageView::OnFileOpen()
{
	LPCTSTR filter = _T("信息文件 (*.dat)|*.dat|所有文件 (*.*)|*.*||");
	CFileDialog fd(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (IDCANCEL == fd.DoModal())
		return;

	// 方法三：CDocument + Serialize
	m_file = fd.GetPathName();
	//m_doc.OnOpenDocument(m_file);
	//m_doc.SetPathName(m_file);
	GetDocument()->OnOpenDocument(m_file);
	GetDocument()->SetPathName(m_file);

	AfxGetMainWnd()->SetWindowText(fd.GetFileName());

	//m_file = fd.GetPathName();			//路径名，绝对路径
	////m_file = fd.GetFileName();		//文件名，相对路径

	//m_list.DeleteAllItems();		//清除所有项

	//CFile file;
	//if (!file.Open(m_file, CFile::modeRead))
	//{
	//	AfxMessageBox(_T("打开文件失败！"));
	//	return;
	//} 
	//// 方法一：CFile + struct SInfo
	////struct SInfo info;
	////CString str;
	////int item = 0;
	////while (file.Read(&info, sizeof(info)) == sizeof(info))
	////{
	////	str.Format(_T("%d"), info.number);
	////	m_list.InsertItem(item, str);
	////	m_list.SetItemText(item, 1, info.name);
	////	m_list.SetItemText(item, 2, info.datetime.Format());
	////	item++;
	////}
	////file.Close();

	//// 方法二：CArchive
	//// 串行化存储对文件版本和存储顺序要求非常严格，存储不对称性会加载失败
	//CArchive archive(&file, CArchive::load);
	//int count = 0;
	//archive >> count;
	//int number = 0;
	//CString str = _T("");
	//DATE date;
	//COleDateTime datetime;
	//for (int item = 0; item < count; item++)
	//{
	//	archive >> number;
	//	str.Format(_T("%d"), number);
	//	m_list.InsertItem(item, str);

	//	archive >> str;
	//	m_list.SetItemText(item, 1, str);

	//	archive >> date;
	//	datetime = date;
	//	m_list.SetItemText(item, 2, datetime.Format());
	//}

}

 //文件 | 保存
void CInfoManageView::OnFileSave()
{
	if (m_file.IsEmpty())
		this->OnFileSaveAs();

	// 方法三：CDocument + Serialize
	//m_doc.OnSaveDocument(m_file);
	//m_doc.SetModifiedFlag(0);
	GetDocument()->OnSaveDocument(m_file);
	GetDocument()->SetModifiedFlag(0);

	AfxGetMainWnd()->SetWindowText(m_file);

	//CFile file;
	//if (!file.Open(m_file, CFile::modeCreate | CFile::modeWrite))
	//{
	//	AfxMessageBox(_T("保存时打开文件失败！"));
	//	return;
	//}

	////// 方法一：CFile + struct SInfo
	////struct SInfo info;
	////int count = m_list.GetItemCount();
	////for (int item = 0; item < count; item++)
	////{	
	////	info.number = _tstoi(m_list.GetItemText(item, 0));
	////	m_list.GetItemText(item, 1, info.name, sizeof(info.name));
	////	info.datetime.ParseDateTime(m_list.GetItemText(item, 2));
	////	file.Write(&info, sizeof(info));
	////}
	////file.Close();

	//// 方法二：CArchive
	//CArchive archive(&file, CArchive::store);
	//int count = m_list.GetItemCount();
	//archive << count;							//先存个总数来着
	//COleDateTime date;
	//for (int item = 0; item < count; item++)
	//{
	//	archive << _tstoi(m_list.GetItemText(item, 0));
	//	archive << m_list.GetItemText(item, 1);
	//	date.ParseDateTime(m_list.GetItemText(item, 2));
	//	archive << (DATE)date;					//转为DATE存储八个字节，减少空间
	//}

}

 //文件 | 另存为...
void CInfoManageView::OnFileSaveAs()
{
	LPCTSTR filter = _T("信息文件 (*.dat)|*.dat|所有文件 (*.*)|*.*||");
	CFileDialog fd(FALSE, _T("dat"), nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (IDCANCEL == fd.DoModal())
		return;

	m_file = fd.GetPathName();
	//m_file = fd.GetFileName();

	//m_doc.OnSaveDocument(fd.GetPathName());

	//m_doc.SetModifiedFlag(0);
}


void CInfoManageView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE p = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	this->OnEditMod();

	*pResult = 0;
}


void CInfoManageView::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		int count = m_list.GetItemCount();
		ar << count;							//先存个总数来着
		COleDateTime date;
		for (int item = 0; item < count; item++)
		{
			ar << _tstoi(m_list.GetItemText(item, 0));
			ar << m_list.GetItemText(item, 1);
			date.ParseDateTime(m_list.GetItemText(item, 2));
			ar << (DATE)date;					//转为DATE存储八个字节，减少空间
		}

	}
	else
	{	
		int count = 0;
		ar >> count;
		int number = 0;
		CString str = _T("");
		DATE date;
		COleDateTime datetime;
		for (int item = 0; item < count; item++)
		{
			ar >> number;
			str.Format(_T("%d"), number);
			m_list.InsertItem(item, str);

			ar >> str;
			m_list.SetItemText(item, 1, str);

			ar >> date;
			datetime = date;
			m_list.SetItemText(item, 2, datetime.Format());
		}

	}
}

void CInfoManageView::DeleteContents()
{
	m_list.DeleteAllItems();
	//for(int i = 2; i >= 0; i--)
	//	m_list.DeleteColumn(i);
}
