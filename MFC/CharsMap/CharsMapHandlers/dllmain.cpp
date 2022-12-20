// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "CharsMapHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CCharsMapHandlersModule _AtlModule;

class CCharsMapHandlersApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCharsMapHandlersApp, CWinApp)
END_MESSAGE_MAP()

CCharsMapHandlersApp theApp;

BOOL CCharsMapHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CCharsMapHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
