// TopView.cpp: 实现文件
//

#include "stdafx.h"
#include "MyOutlook.h"
#include "TopView.h"


// CTopView

IMPLEMENT_DYNCREATE(CTopView, CListView)

CTopView::CTopView() : m_list(GetListCtrl())
{
	theApp.m_pTopView = this;
}

CTopView::~CTopView()
{
}

BEGIN_MESSAGE_MAP(CTopView, CListView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CTopView::OnLvnItemchanged)
END_MESSAGE_MAP()


// CTopView 诊断

#ifdef _DEBUG
void CTopView::RegAccess(HKEY hKey, CString szSubKey)
{
	// eg. 计算机\HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\TypedUrls
	HKEY hkResult = nullptr;
	LSTATUS res = RegOpenKeyEx(hKey, szSubKey, 0, KEY_ALL_ACCESS, &hkResult);
	if (res)	// 0 - success, !0 - failure
		return;

	CString value;
	int item = m_list.GetItemCount();
	for (int i = 0; i < 100; i++)
	{
		BYTE data[2048] = { 0 };
		DWORD cbdata = sizeof(data);
		value.Format(_T("url%d"), i + 1);
		if (ERROR_SUCCESS != RegQueryValueEx(hkResult, value, 0, nullptr, data, &cbdata))
			break;

		m_list.InsertItem(item++, value + _T(" ") + (LPCTSTR)data);
	}
}
/***
#define HKEY_CLASSES_ROOT                   (( HKEY ) (ULONG_PTR)((LONG)0x80000000) )
#define HKEY_CURRENT_USER                   (( HKEY ) (ULONG_PTR)((LONG)0x80000001) )
#define HKEY_LOCAL_MACHINE                  (( HKEY ) (ULONG_PTR)((LONG)0x80000002) )
#define HKEY_USERS                          (( HKEY ) (ULONG_PTR)((LONG)0x80000003) )
#define HKEY_PERFORMANCE_DATA               (( HKEY ) (ULONG_PTR)((LONG)0x80000004) )
#define HKEY_PERFORMANCE_TEXT               (( HKEY ) (ULONG_PTR)((LONG)0x80000050) )
#define HKEY_PERFORMANCE_NLSTEXT            (( HKEY ) (ULONG_PTR)((LONG)0x80000060) )
#if (WINVER >= 0x0400)
#define HKEY_CURRENT_CONFIG                 (( HKEY ) (ULONG_PTR)((LONG)0x80000005) )
#define HKEY_DYN_DATA                       (( HKEY ) (ULONG_PTR)((LONG)0x80000006) )
#define HKEY_CURRENT_USER_LOCAL_SETTINGS    (( HKEY ) (ULONG_PTR)((LONG)0x80000007) )

#define ERROR_SUCCESS                    0L
typedef _Return_type_success_(return==ERROR_SUCCESS) LONG LSTATUS;
WINADVAPI LSTATUS APIENTRY RegOpenKeyExW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_opt_ DWORD ulOptions,
	_In_ REGSAM samDesired,
	_Out_ PHKEY phkResult
	);

WINADVAPI LSTATUS APIENTRY RegQueryValueExW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName,
	_Reserved_ LPDWORD lpReserved,
	_Out_opt_ LPDWORD lpType,
	_Out_writes_bytes_to_opt_(*lpcbData, *lpcbData) __out_data_source(REGISTRY) LPBYTE lpData,
	_When_(lpData == NULL,_Out_opt_) _When_(lpData != NULL,_Inout_opt_) LPDWORD lpcbData
	);


***/

void CTopView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopView 消息处理程序


BOOL CTopView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle = 0;

	return CListView::PreCreateWindow(cs);
}


void CTopView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	m_list.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("收件人"), 0, 200);
	m_list.InsertColumn(1, _T("主题"), 0, 200);
	m_list.InsertColumn(2, _T("接受时间"), 0, 200);
	
	m_list.InsertItem(0, _T("Microsoft Outlook"));


}


void CTopView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	theApp.m_pBottomView->Navigate2(_T("www.baidu.com"));

	// 计算机\HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\TypedUrls
	this->RegAccess(HKEY_CURRENT_USER, 
		_T("Software\\Microsoft\\Internet Explorer\\TypedUrls"));

	*pResult = 0;
}
