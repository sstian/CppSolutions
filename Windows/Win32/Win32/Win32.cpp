// Win32 Application
#include <Windows.h>
#include <windowsx.h>	//GET_X_LPARAM  GET_Y_LPARAM
#include <tchar.h>
#include "resource.h"

#define TIMER_1 0x0001	//定时器ID

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

// 回调函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// 对话框回调函数
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
// 登录对话框回调函数
INT_PTR CALLBACK LoginDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// double 存取
DOUBLE GetDlgItemDouble(HWND hwnd, UINT uID);
VOID SetDlgItemDouble(HWND hwnd, UINT uID, DOUBLE dValue);

// 使窗口在屏幕居中
VOID WindowCenter(HWND hwnd);

// 初始化登录对话框
VOID OnInitDialog(HWND hwndDlg);
// 登录
VOID Onlogin(HWND hwndDlg);

// 入口函数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrecIntance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	// 一、桌面窗口
	//// 设计窗口类
	//WNDCLASSEX wcex;
	//wcex.cbSize = sizeof(WNDCLASSEX);
	//wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = WindowProc;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	//wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	//wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//wcex.lpszMenuName = NULL;
	//wcex.lpszClassName = szWindowClass;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_ERROR);
	//// 注册窗口
	//if (!RegisterClassEx(&wcex))
	//{
	//	MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Exit."), NULL);
	//	return 1;
	//}
	//// 创建窗口
	//HWND hwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, 640, 480,
	//	NULL, NULL, hInstance, NULL);
	//if (!hwnd)
	//{
	//	MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Wind32 Guided Exit."), NULL);
	//	return 1;
	//}
	//// 显示窗口
	//ShowWindow(hwnd, nCmdShow);
	//// 更新窗口
	//UpdateWindow(hwnd);
	//// 消息循环
	//MSG msg;
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
	//return (int)msg.wParam;
	
	// 二、对话框
	//if(IDOK == DialogBox(hInstance, (LPCTSTR)IDD_LOGIN_DIALOG, NULL, LoginDialogProc))
		DialogBox(hInstance, (LPCTSTR)IDD_DIALOG, NULL, DialogProc);
	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	TCHAR painting[] = _T("Hello World!");
	TCHAR mouseClick[] = _T("你踩着我的尾巴了！");
	WCHAR sztchar[20] = { 0 };

	switch (uMsg)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 0, 0, painting, (int)_tcslen(painting));
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		swprintf_s(sztchar, _T("tchar is %c."), (char)wParam);
		MessageBox(hwnd, sztchar, _T("按了一下键"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, _T("Mouse clicked."), _T("点你"), 0);
		hdc = GetDC(hwnd);
		TextOut(hdc, 30, 30, mouseClick, (int)_tcslen(mouseClick));
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, _T("您真的要退出吗？"), _T("Goodbye"), MB_YESNO))
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


DOUBLE GetDlgItemDouble(HWND hwnd, UINT uID)
{
	TCHAR tchar[20] = { 0 };
	GetDlgItemText(hwnd, uID, tchar, sizeof(tchar));
	return _tcstod(tchar, nullptr);
}
VOID SetDlgItemDouble(HWND hwnd, UINT uID, DOUBLE dValue)
{
	TCHAR tchar[20] = { 0 };
	_stprintf_s(tchar, _T("%lf"), dValue);
	SetDlgItemText(hwnd, uID, tchar);
}
VOID WindowCenter(HWND hwnd)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	MoveWindow(hwnd, (cx - width) / 2, (cy - height) / 2, width, height, TRUE);
}
INT_PTR DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)	//消息分流
	{
	case WM_INITDIALOG:	//对话框出现前初始化
	{
		WindowCenter(hwndDlg);
		SetWindowText(hwndDlg, _T("Calculator Test"));
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwndDlg, &ps);		//开始绘制，并获得设备句柄
		RECT rect;
		GetClientRect(hwndDlg, &rect);			//获得客户区矩形区域
		MoveToEx(hdc, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2, NULL);	//移动到中心点
		LineTo(hdc, rect.left, rect.bottom);	//划线
		EndPaint(hwndDlg, &ps);					//结束绘制
		break;
	}
	case WM_COMMAND:	//命令消息
	//窗口菜单：LOWORD(wParam): 菜单id，HIWORD(wParam): 0，lParam: 0
	//子窗口控件：LOWORD(wParam): 控件ID，HIWORD(wParam): 通知码，lParam: 子窗口句柄。
		if (IDOK == LOWORD(wParam))
		{
			int left = GetDlgItemInt(hwndDlg, IDC_LEFT, NULL, TRUE);
			int right = GetDlgItemInt(hwndDlg, IDC_RIGHT, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT, left + right, TRUE);
		}
		if (IDOK2 == LOWORD(wParam))
		{
			double left2 = GetDlgItemDouble(hwndDlg, IDC_LEFT2);
			double right2 = GetDlgItemDouble(hwndDlg, IDC_RIGHT2);
			SetDlgItemDouble(hwndDlg, IDC_RESULT2, left2 * right2);
		}
		if (IDCANCEL == LOWORD(wParam) || ID_MENU_EXIT == LOWORD(wParam))
		{
			EndDialog(hwndDlg, IDCANCEL);
		}
		if (ID_MENU_ABOUT == LOWORD(wParam))	//菜单：帮助 | 关于...
		{
			TCHAR tchar[20] = { 0 };
			LoadString(NULL, IDS_STRING104, tchar, sizeof(tchar));
			MessageBox(hwndDlg, tchar, _T("About"), 0);
		}
		if (ID_MENU_SYSTEM == LOWORD(wParam))	//菜单：帮助 | SystemDirectory...
		{
			TCHAR tchar[100] = { 0 };
			GetSystemDirectory(tchar, sizeof(tchar));		//C:\WINDOWS\system32
			MessageBox(hwndDlg, tchar, _T("GetSystemDirectory()"), 0);
		}
		if (ID_MENU_MODULE == LOWORD(wParam))	//菜单：帮助 | ModuleFileName...
		{
			TCHAR tchar[100] = { 0 };
			GetModuleFileName(NULL, tchar, sizeof(tchar));	//Win32.exe运行的目录
			MessageBox(hwndDlg, tchar, _T("GetModuleFileName()"), 0);
		}
		return TRUE;
	case WM_RBUTTONDOWN:
	{
		short x = LOWORD(lParam);
		short y = HIWORD(lParam);
		TCHAR tchar[20] = { 0 };
		_stprintf_s(tchar, _T("右键按下：x=%d, y=%d"), x, y);
		SetWindowText(hwndDlg, tchar);
		break;
	}
	case WM_MOUSEMOVE:
	//wParam: 指示是否其它键被按下
	//lParam: 低字节表示光标的X坐标，高字节表示光标的Y坐标，坐标是相对于客户区域的左上角。
	{
		//short x = LOWORD(lParam);
		//short y = HIWORD(lParam);
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		TCHAR tchar[100] = { 0 };
		_stprintf_s(tchar, _T("光标移动：x=%d, y=%d"), x, y);
		if (wParam & MK_LBUTTON)
			_tcscat_s(tchar, sizeof(tchar), _T(" 左键按下"));
		if (wParam & MK_RBUTTON)
			_tcscat_s(tchar, sizeof(tchar), _T(" 右键按下"));
		if (wParam & MK_CONTROL)
			_tcscat_s(tchar, sizeof(tchar), _T(" Ctrl按下"));
		if (wParam & MK_SHIFT)
			_tcscat_s(tchar, sizeof(tchar), _T(" Shift按下"));
		if(GetKeyState(VK_MENU) < 0)
			_tcscat_s(tchar, sizeof(tchar), _T(" Alt按下"));

		SetWindowText(hwndDlg, tchar);
		break;
	}
	default:
		break;
	}
	return FALSE;	//缺省处理由系统完成
}

VOID OnInitDialog(HWND hwndDlg)
{
	WindowCenter(hwndDlg);
	SetTimer(hwndDlg, TIMER_1, 1000, NULL);	//设置定时器
	
}
VOID Onlogin(HWND hwndDlg)
{
	TCHAR username[20] = { 0 };
	TCHAR password[20] = { 0 };
	GetDlgItemText(hwndDlg, IDC_EDIT_USERNAME, username, sizeof(username));
	GetDlgItemText(hwndDlg, IDC_EDIT_PASSWORD, password, sizeof(password));
	if (_tcscmp(username, _T("admin")) || _tcscmp(password, _T("123456")))
	{
		//MessageBox(hwndDlg, _T("用户名或密码错误！"), _T("残念"), MB_OK);
		SetDlgItemText(hwndDlg, IDC_STATUS, _T("残念：用户名或密码错误！"));
		return;
	}
	SetDlgItemText(hwndDlg, IDC_STATUS, _T("登录成功，欢迎光临"));
	EndDialog(hwndDlg, IDOK);
	KillTimer(hwndDlg, TIMER_1);	//关闭定时器
}
INT_PTR LoginDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialog(hwndDlg);
		return TRUE;
	case WM_SETCURSOR:
		//wParam: 当前使用的光标句柄
		//lParam: LOWORD - 当前区域的代码(HTCLIENT/HTCAPTION)，HIWORD - 当前鼠标消息ID.
		//SetDlgItemText(hwndDlg, IDC_STATUS, _T(""));	//先清空状态显示
		if (HTCAPTION == LOWORD(lParam))
			SetDlgItemText(hwndDlg, IDC_STATUS, _T("Login Dialog"));
		if ((HWND)wParam == GetDlgItem(hwndDlg, IDC_EDIT_USERNAME))
			SetDlgItemText(hwndDlg, IDC_STATUS, _T("请在此处输入用户名"));
		if ((HWND)wParam == GetDlgItem(hwndDlg, IDC_EDIT_PASSWORD))
			SetDlgItemText(hwndDlg, IDC_STATUS, _T("请在此处输入密码"));
		return TRUE;
	case WM_TIMER:	//定时器消息
	//WM_TIMER wTimerID = wParam;
	//tmprc = (TIMERPROC *)lParam;
		switch (wParam)
		{
		case TIMER_1:
		{
			TCHAR strtime[30] = { 0 };
			SYSTEMTIME stime;
			GetLocalTime(&stime);
			_stprintf_s(strtime, _T("%d-%02d-%02d %02d:%02d:%02d"),
				stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
			SetDlgItemText(hwndDlg, IDC_DATETIME, strtime);
			break;
		}
		default:
			break;
		}
		break;
	case WM_COMMAND:
		if (IDCANCEL == LOWORD(wParam))
			EndDialog(hwndDlg, IDCANCEL);
		if (IDOK == LOWORD(wParam))
			Onlogin(hwndDlg);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

/*** Unicode
typedef int                 BOOL;
#define TRUE                1
#define FALSE               0

DECLARE_HANDLE(HINSTANCE);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE            (HWND);
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall

typedef struct tagWNDCLASSEXW {
	UINT        cbSize;
	UINT        style;
	WNDPROC     lpfnWndProc;
	int         cbClsExtra;
	int         cbWndExtra;
	HINSTANCE   hInstance;
	HICON       hIcon;
	HCURSOR     hCursor;
	HBRUSH      hbrBackground;
	LPCWSTR     lpszMenuName;
	LPCWSTR     lpszClassName;
	HICON       hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;

ATOM WINAPI RegisterClassExW(_In_ CONST WNDCLASSEXW *);

int WINAPI MessageBoxW(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_ UINT uType);

HWND WINAPI CreateWindow(
	_In_ DWORD dwExStyle,
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName,
	_In_ DWORD dwStyle,
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID lpParam);

BOOL WINAPI ShowWindow(_In_ HWND hWnd, _In_ int nCmdShow);

BOOL WINAPI UpdateWindow(_In_ HWND hWnd);

BOOL WINAPI GetMessage(
	_Out_ LPMSG lpMsg,
	_In_opt_ HWND hWnd,
	_In_ UINT wMsgFilterMin,
	_In_ UINT wMsgFilterMax);

BOOL WINAPI TranslateMessage(_In_ CONST MSG *lpMsg);

LRESULT WINAPI DispatchMessageW(_In_ CONST MSG *lpMsg);

typedef struct tagPAINTSTRUCT {
	HDC         hdc;
	BOOL        fErase;
	RECT        rcPaint;
	BOOL        fRestore;
	BOOL        fIncUpdate;
	BYTE        rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

HDC WINAPI BeginPaint(_In_ HWND hWnd, _Out_ LPPAINTSTRUCT lpPaint);
BOOL WINAPI EndPaint(_In_ HWND hWnd, _In_ CONST PAINTSTRUCT *lpPaint);

HDC WINAPI GetDC(_In_opt_ HWND hWnd);
int WINAPI ReleaseDC(_In_opt_ HWND hWnd, _In_ HDC hDC);

BOOL  WINAPI TextOutW( _In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCWSTR lpString, _In_ int c);

BOOL WINAPI DestroyWindow(_In_ HWND hWnd);

VOID WINAPI PostQuitMessage(_In_ int nExitCode);

LRESULT WINAPI DefWindowProc(
	_In_ HWND hWnd,
	_In_ UINT Msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);

===============================================================================
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

// Key State Masks for Mouse Messages
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010

// Virtual Keys, Standard Set
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04   

#define VK_BACK           0x08
#define VK_TAB            0x09

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
#define VK_HANGEUL        0x15  
#define VK_HANGUL         0x15

#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

#define VK_ESCAPE         0x1B

#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D
#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#define VK_NAVIGATION_VIEW     0x88 // reserved
#define VK_NAVIGATION_MENU     0x89 // reserved
#define VK_NAVIGATION_UP       0x8A // reserved
#define VK_NAVIGATION_DOWN     0x8B // reserved
#define VK_NAVIGATION_LEFT     0x8C // reserved
#define VK_NAVIGATION_RIGHT    0x8D // reserved
#define VK_NAVIGATION_ACCEPT   0x8E // reserved
#define VK_NAVIGATION_CANCEL   0x8F // reserved

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad
#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

#define VK_GAMEPAD_A                         0xC3 // reserved
#define VK_GAMEPAD_B                         0xC4 // reserved
#define VK_GAMEPAD_X                         0xC5 // reserved
#define VK_GAMEPAD_Y                         0xC6 // reserved
#define VK_GAMEPAD_RIGHT_SHOULDER            0xC7 // reserved
#define VK_GAMEPAD_LEFT_SHOULDER             0xC8 // reserved
#define VK_GAMEPAD_LEFT_TRIGGER              0xC9 // reserved
#define VK_GAMEPAD_RIGHT_TRIGGER             0xCA // reserved
#define VK_GAMEPAD_DPAD_UP                   0xCB // reserved
#define VK_GAMEPAD_DPAD_DOWN                 0xCC // reserved
#define VK_GAMEPAD_DPAD_LEFT                 0xCD // reserved
#define VK_GAMEPAD_DPAD_RIGHT                0xCE // reserved
#define VK_GAMEPAD_MENU                      0xCF // reserved
#define VK_GAMEPAD_VIEW                      0xD0 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON    0xD1 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON   0xD2 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_UP        0xD3 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_DOWN      0xD4 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT     0xD5 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_LEFT      0xD6 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_UP       0xD7 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN     0xD8 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT    0xD9 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT     0xDA // reserved

#define VK_OEM_4          0xDB  //  '[{' for US
#define VK_OEM_5          0xDC  //  '\|' for US
#define VK_OEM_6          0xDD  //  ']}' for US
#define VK_OEM_7          0xDE  //  ''"' for US
#define VK_OEM_8          0xDF


// GetSystemMetrics() codes
#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXVSCROLL            2
#define SM_CYHSCROLL            3
#define SM_CYCAPTION            4
#define SM_CXBORDER             5
#define SM_CYBORDER             6
#define SM_CXDLGFRAME           7
#define SM_CYDLGFRAME           8
#define SM_CYVTHUMB             9
#define SM_CXHTHUMB             10
#define SM_CXICON               11
#define SM_CYICON               12
#define SM_CXCURSOR             13
#define SM_CYCURSOR             14
#define SM_CYMENU               15
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CYKANJIWINDOW        18
#define SM_MOUSEPRESENT         19
#define SM_CYVSCROLL            20
#define SM_CXHSCROLL            21
#define SM_DEBUG                22
#define SM_SWAPBUTTON           23
#define SM_RESERVED1            24
#define SM_RESERVED2            25
#define SM_RESERVED3            26
#define SM_RESERVED4            27
#define SM_CXMIN                28
#define SM_CYMIN                29
#define SM_CXSIZE               30
#define SM_CYSIZE               31
#define SM_CXFRAME              32
#define SM_CYFRAME              33
#define SM_CXMINTRACK           34
#define SM_CYMINTRACK           35
#define SM_CXDOUBLECLK          36
#define SM_CYDOUBLECLK          37
#define SM_CXICONSPACING        38
#define SM_CYICONSPACING        39
#define SM_MENUDROPALIGNMENT    40
#define SM_PENWINDOWS           41
#define SM_DBCSENABLED          42
#define SM_CMOUSEBUTTONS        43

// MessageBox() Flags
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
#if(WINVER >= 0x0500)
#define MB_CANCELTRYCONTINUE        0x00000006L
#endif 

#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L

#if(WINVER >= 0x0400)
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
#endif

#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND

#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#if(WINVER >= 0x0400)
#define MB_DEFBUTTON4               0x00000300L
#endif 

#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L
#if(WINVER >= 0x0400)
#define MB_HELP                     0x00004000L // Help Button
#endif 

#define MB_NOFOCUS                  0x00008000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L

#if(WINVER >= 0x0400)
#define MB_TOPMOST                  0x00040000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L
#endif 

#define MB_TYPEMASK                 0x0000000FL
#define MB_ICONMASK                 0x000000F0L
#define MB_DEFMASK                  0x00000F00L
#define MB_MODEMASK                 0x00003000L
#define MB_MISCMASK                 0x0000C000L

// Window Messages
#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005
#define WM_ACTIVATE                     0x0006
	//WM_ACTIVATE state values
	#define     WA_INACTIVE     0
	#define     WA_ACTIVE       1
	#define     WA_CLICKACTIVE  2
#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A
#if(WINVER >= 0x0400)
#define WM_SETTINGCHANGE                WM_WININICHANGE
#endif 

#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023
#define WM_GETMINMAXINFO                0x0024

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039

#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047

#define WM_POWER                        0x0048
#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B

#if(WINVER >= 0x0400)
#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9

#if(_WIN32_WINNT >= 0x0500)
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif 

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107

#if(WINVER >= 0x0400)
#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F
#endif 

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#if(WINVER >= 0x0601)
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A
#endif 
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1

#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSEHWHEEL                  0x020E
#endif

#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSELAST                    0x020E
#elif (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSELAST                    0x020A
#else
#define WM_MOUSELAST                    0x0209
#endif 

#if(_WIN32_WINNT >= 0x0400)
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif 

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))
#endif 

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif 

INT_PTR WINAPI DialogBox(
	_In_opt_ HINSTANCE hInstance,
	_In_ LPCWSTR lpTemplateName,
	_In_opt_ HWND hWndParent,
	_In_opt_ DLGPROC lpDialogFunc,
	_In_ LPARAM dwInitParam);

typedef struct tagRECT
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;
typedef const RECT FAR* LPCRECT;

typedef struct tagPOINT
{
	LONG  x;
	LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct tagSIZE
{
	LONG        cx;
	LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

BOOL WINAPI EndDialog(_In_ HWND hDlg, _In_ INT_PTR nResult);

HWND WINAPI GetDlgItem(_In_opt_ HWND hDlg, _In_ int nIDDlgItem);

UINT WINAPI GetDlgItemInt(
	_In_ HWND hDlg,
	_In_ int nIDDlgItem,
	_Out_opt_ BOOL *lpTranslated,
	_In_ BOOL bSigned);

BOOL WINAPI SetDlgItemInt(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ UINT uValue,
    _In_ BOOL bSigned);

UINT WINAPI GetDlgItemText(
	_In_ HWND hDlg,
	_In_ int nIDDlgItem,
	_Out_writes_(cchMax) LPSTR lpString,
	_In_ int cchMax);

BOOL WINAPI SetDlgItemText(
	_In_ HWND hDlg,
	_In_ int nIDDlgItem,
	_In_ LPCSTR lpString);

int WINAPI GetWindowText(
	_In_ HWND hWnd,
	_Out_writes_(nMaxCount) LPWSTR lpString,
	_In_ int nMaxCount);

BOOL WINAPI SetWindowText(_In_ HWND hWnd, _In_opt_ LPCSTR lpString);

BOOL WINAPI GetClientRect(_In_ HWND hWnd, _Out_ LPRECT lpRect);

BOOL WINAPI GetWindowRect(_In_ HWND hWnd, _Out_ LPRECT lpRect);

BOOL WINAPI MoveWindow(
	_In_ HWND hWnd,
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_ BOOL bRepaint);

int WINAPI GetSystemMetrics(_In_ int nIndex);

SHORT WINAPI GetKeyState(_In_ int nVirtKey);

HWND WINAPI SetFocus(_In_opt_ HWND hWnd);
HWND WINAPI GetFocus(VOID);

UINT_PTR WINAPI SetTimer(
	_In_opt_ HWND hWnd,
	_In_ UINT_PTR nIDEvent,
	_In_ UINT uElapse,
	_In_opt_ TIMERPROC lpTimerFunc);

BOOL WINAPI KillTimer(
	_In_opt_ HWND hWnd,
	_In_ UINT_PTR uIDEvent);

int WINAPI LoadStringW(
	_In_opt_ HINSTANCE hInstance,
	_In_ UINT uID,
	_Out_writes_to_(cchBufferMax,return + 1) LPWSTR lpBuffer,
	_In_ int cchBufferMax
	);

UINT WINAPI GetSystemDirectoryW(
	_Out_writes_to_opt_(uSize,return + 1) LPWSTR lpBuffer,
	_In_ UINT uSize
	);

DWORD WINAPI GetModuleFileNameW(
	_In_opt_ HMODULE hModule,
	_Out_writes_to_(nSize,((return < nSize) ? (return + 1) : nSize)) LPWSTR lpFilename,
	_In_ DWORD nSize
	);

BOOL WINAPI GetClientRect(_In_ HWND hWnd, _Out_ LPRECT lpRect);

WINGDIAPI BOOL  WINAPI MoveToEx( _In_ HDC hdc, _In_ int x, _In_ int y, _Out_opt_ LPPOINT lppt);
WINGDIAPI BOOL	WINAPI LineTo( _In_ HDC hdc, _In_ int x, _In_ int y);

*/