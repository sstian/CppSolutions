#include "pch.h"
#include "RegEdit.h"

HKEY CRegEdit::SRootKey::KEY_CLASSES_ROOT	= HKEY_CLASSES_ROOT;
HKEY CRegEdit::SRootKey::KEY_CURRENT_USER	= HKEY_CURRENT_USER;
HKEY CRegEdit::SRootKey::KEY_LOCAL_MACHINE	= HKEY_LOCAL_MACHINE;
HKEY CRegEdit::SRootKey::KEY_USERS			= HKEY_USERS;
HKEY CRegEdit::SRootKey::KEY_CURRENT_CONFIG	= HKEY_CURRENT_CONFIG;


CRegEdit::CRegEdit()
{
	
}


CRegEdit::~CRegEdit()
{
	CloseKey();
}

BOOL CRegEdit::OpenKey(HKEY hRootKey, LPCTSTR szSubKey, enum EAccess access)
{
	m_rootKey = hRootKey;
	m_szSubKey = szSubKey;
	m_access = access;

	LONG nError = RegOpenKeyEx(m_rootKey, m_szSubKey, 0, m_access, &m_key);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::CreateKey(DWORD* out_dwDisposition)
{
	DWORD dwDisposition;
	LONG nError = RegCreateKeyEx(
		m_rootKey, m_szSubKey, 0,
		const_cast<LPTSTR>(_T("State")),
		REG_OPTION_NON_VOLATILE,
		m_access, NULL, &m_key, &dwDisposition);
	
	if (out_dwDisposition)
		*out_dwDisposition = dwDisposition;

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::SetValue(LPCTSTR szKeyName, LPCTSTR szValueData)
{
	DWORD cbData = static_cast<DWORD>(_tcslen(szValueData) + 1);
	LONG nError = RegSetValue(
		m_key, szKeyName,
		REG_SZ, 
		szValueData, cbData);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::SetValueEx(LPCTSTR szValueName, LPCTSTR szValueData)
{
	DWORD cbData = static_cast<DWORD>(_tcslen(szValueData) + 1);
#ifdef UNICODE
	cbData *= 2;
#endif // UNICODE

	LONG nError = RegSetValueEx(
		m_key, szValueName,0,
		REG_SZ, 
		(CONST BYTE*)szValueData, cbData);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::SetValueEx(LPCTSTR szValueName, DWORD dwValueData)
{
	LONG nError = RegSetValueEx(
		m_key, szValueName, 0,
		REG_DWORD,
		(CONST BYTE*)&dwValueData, sizeof(DWORD));

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::SetValueEx(LPCTSTR szValueName, LPBYTE byValueData, DWORD cdData)
{
	LONG nError = RegSetValueEx(
		m_key, szValueName, 0,
		REG_BINARY,
		byValueData, cdData);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::GetValue(LPCTSTR szKeyName, CString& strValueData)
{
	TCHAR value[MAX_PATH] = { 0 };
	LONG data = sizeof(value);

	LONG nError = RegQueryValue(m_key, szKeyName, value, &data);
	if (ERROR_SUCCESS == nError)
		strValueData = value;
	
	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::GetValueEx(LPCTSTR szValueName, CString & strValueData)
{
	DWORD type = REG_SZ;
	DWORD data = MAX_PATH;

	LONG nError = RegQueryValueEx(
		m_key, szValueName, 0,
		&type,
		reinterpret_cast<LPBYTE>(strValueData.GetBuffer(MAX_PATH)), &data);

	strValueData.ReleaseBuffer();

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::GetValueEx(LPCTSTR szValueName, DWORD & dwValueData)
{
	DWORD type = REG_DWORD;
	DWORD data = sizeof(DWORD);

	LONG nError = RegQueryValueEx(
		m_key, szValueName, 0,
		&type,
		reinterpret_cast<LPBYTE>(&dwValueData), &data);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::GetValueEx(LPCTSTR szValueName, LPBYTE byValueData, DWORD& cdData)
{
	DWORD type = REG_BINARY;
	//DWORD data = MAX_PATH;

	LONG nError = RegQueryValueEx(
		m_key, szValueName, 0,
		&type,
		byValueData, &cdData);

	return ERROR_SUCCESS == nError;
}

BOOL CRegEdit::DeleteValue(LPCTSTR szKeyName)
{
	return ERROR_SUCCESS == RegDeleteKey(m_key, szKeyName);
}

BOOL CRegEdit::DeleteValueEx(LPCTSTR szValueName)
{
	////注意：使用RegDeleteKeyEx(...)，要删除的子键必须没有子项
	//return ERROR_SUCCESS == RegDeleteKeyEx(m_key, szValueName, KEY_WOW64_32KEY, 0);
	
	return ERROR_SUCCESS == RegDeleteValue(m_key, szValueName);
}

BOOL CRegEdit::CloseKey()
{
	return ERROR_SUCCESS == RegCloseKey(m_key);
}

/**
<winreg.h>
// 1. 打开一个指定的注册表键
WINADVAPI LSTATUS APIENTRY 
RegOpenKeyExW(
	_In_ HKEY hKey,				//需要打开的主键的名称
	_In_opt_ LPCWSTR lpSubKey,	//需要打开的子键的名称，输入以null结尾的字符串指针
	_In_opt_ DWORD ulOptions,	// 保留，设为0
	_In_ REGSAM samDesired,		// 安全访问标记，也就是权限
	_Out_ PHKEY phkResult		// 得到的将要打开键的句柄
	);
hKey:
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

samDesired:
// Registry Specific Access Rights.
#define KEY_QUERY_VALUE         (0x0001)
#define KEY_SET_VALUE           (0x0002)
#define KEY_CREATE_SUB_KEY      (0x0004)
#define KEY_ENUMERATE_SUB_KEYS  (0x0008)
#define KEY_NOTIFY              (0x0010)
#define KEY_CREATE_LINK         (0x0020)
#define KEY_WOW64_32KEY         (0x0200)	// 32位注册表视图
#define KEY_WOW64_64KEY         (0x0100)	// 64位注册表视图
#define KEY_WOW64_RES           (0x0300)

#define KEY_READ                ((STANDARD_RIGHTS_READ       |\
								  KEY_QUERY_VALUE            |\
								  KEY_ENUMERATE_SUB_KEYS     |\
								  KEY_NOTIFY)                 \
								  &                           \
								 (~SYNCHRONIZE))


#define KEY_WRITE               ((STANDARD_RIGHTS_WRITE      |\
								  KEY_SET_VALUE              |\
								  KEY_CREATE_SUB_KEY)         \
								  &                           \
								 (~SYNCHRONIZE))

#define KEY_EXECUTE             ((KEY_READ)                   \
								  &                           \
								 (~SYNCHRONIZE))

#define KEY_ALL_ACCESS          ((STANDARD_RIGHTS_ALL        |\
								  KEY_QUERY_VALUE            |\
								  KEY_SET_VALUE              |\
								  KEY_CREATE_SUB_KEY         |\
								  KEY_ENUMERATE_SUB_KEYS     |\
								  KEY_NOTIFY                 |\
								  KEY_CREATE_LINK)            \
								  &                           \
								 (~SYNCHRONIZE))
备注：当指定键不存在 RegOpenKeyEx函数不创建新键
返回值：如果函数调用成功，则返回0（ERROR_SUCCESS）；
		否则，返回值为文件WINERROR.h中定义的一个非零的错误代码。


// 2. 创建指定的注册键
WINADVAPI LSTATUS APIENTRY
RegCreateKeyExW(
	_In_ HKEY hKey,						// 一个打开项的句柄，或者一个标准项名
	_In_ LPCWSTR lpSubKey,				// 欲创建的新子项的名字
	_Reserved_ DWORD Reserved,			// 设为0
	_In_opt_ LPWSTR lpClass,			// 项的类名，指向一个字符串，可以为空，在操作本地和远程注册表时使用
	_In_ DWORD dwOptions,				// 是否保存，在系统重新启动后
	_In_ REGSAM samDesired,				// 访问权限
	_In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// 安全特性，返回的句柄是否可以被子进程继承，为NULL时不能继承
	_Out_ PHKEY phkResult,				// 指定用于装载新子项句柄的一个变量
	_Out_opt_ LPDWORD lpdwDisposition	// 用于接收返回信息
	);
dwOptions: 
// Open/Create Options
#define REG_OPTION_RESERVED         (0x00000000L)   // Parameter is reserved
#define REG_OPTION_NON_VOLATILE     (0x00000000L)   // Key is preserved when system is rebooted
#define REG_OPTION_VOLATILE         (0x00000001L)   // Key is not preserved when system is rebooted 一般使用该值
#define REG_OPTION_BACKUP_RESTORE   (0x00000004L)   // open for backup or restore special access rules privilege required
#define REG_OPTION_OPEN_LINK        (0x00000008L)   // Open symbolic link
#define REG_OPTION_DONT_VIRTUALIZE  (0x00000010L)   // Disable Open/Read/Write

lpdwDisposition:
// Key creation/open disposition
#define REG_CREATED_NEW_KEY         (0x00000001L)   // 新建的一个子项
#define REG_OPENED_EXISTING_KEY     (0x00000002L)   //打开一个现有的项

备注：该函数创建的键没有键值。应用程序不能创建HKEY_USERS 或者 HKEY_LOCAL_MACHINE的直接子键。
返回值：成功则返回 ERROR_SUCCESS.


// 3. 取得指定项或子项的默认（未命名）值
WINADVAPI LSTATUS APIENTRY
RegQueryValueW (
	_In_ HKEY hKey,					// 一个已打开表项的句柄
	_In_opt_ LPCWSTR lpSubKey,		// 指向一个空终止的字符串指针，指示这个函数将打开或创建的表项的名称
	_Out_writes_bytes_to_opt_(*lpcbData, *lpcbData) __out_data_source(REGISTRY) LPWSTR lpData,	//指向一个缓存区，用来获得与指定子项默认值相关的一个字符串
	_Inout_opt_ PLONG lpcbData		// 指定一个变量，用于装载lpValue缓冲区的长度
	);
返回值： 0（ERROR_SUCCESS）表示成功。其他任何值都代表一个错误代码。

// 4.
WINADVAPI LSTATUS APIENTRY
RegSetValueW (
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) LPCWSTR lpData,
	_In_ DWORD cbData
	);
WINADVAPI LSTATUS APIENTRY
RegSetValueExW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName,
	_Reserved_ DWORD Reserved,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) CONST BYTE* lpData,
	_In_ DWORD cbData
	);

dwType:
// Predefined Value Types.
#define REG_NONE                    ( 0ul ) // No value type
#define REG_SZ                      ( 1ul ) // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2ul ) // Unicode nul terminated string (with environment variable references)
#define REG_BINARY                  ( 3ul ) // Free form binary
#define REG_DWORD                   ( 4ul ) // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4ul ) // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5ul ) // 32-bit number
#define REG_LINK                    ( 6ul ) // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7ul ) // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8ul ) // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9ul ) // Resource list in the hardware description
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10ul )
#define REG_QWORD                   ( 11ul ) // 64-bit number
#define REG_QWORD_LITTLE_ENDIAN     ( 11ul ) // 64-bit number (same as REG_QWORD)

// 5.
WINADVAPI LSTATUS APIENTRY
RegSetKeyValueW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_opt_ LPCWSTR lpValueName,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) LPCVOID lpData,
	_In_ DWORD cbData
	);

// 6.
WINADVAPI LSTATUS APIENTRY
RegDeleteKeyExW(
    _In_ HKEY hKey,
    _In_ LPCWSTR lpSubKey,
    _In_ REGSAM samDesired,		// 访问掩码指定注册表的特定于平台的视图
    _Reserved_ DWORD Reserved	// 保留参数，必须为零
    );

// 7. 
WINADVAPI LSTATUSAPIENTRY
RegDeleteKeyValueW(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpSubKey,
    _In_opt_ LPCWSTR lpValueName
    );

//  释放指定注册键的句柄
WINADVAPI LSTATUS APIENTRY
RegCloseKey(
	_In_ HKEY hKey
	);
返回值：0（ERROR_SUCCESS）表示成功。其他任何值都代表一个错误代码


// 
#define WINADVAPI DECLSPEC_IMPORT
#define WINBASEAPI DECLSPEC_IMPORT
#define DECLSPEC_IMPORT __declspec(dllimport)

#define ERROR_SUCCESS                    0L
#define NO_ERROR 0L                                                 // dderror
#define SEC_E_OK                         ((HRESULT)0x00000000L)
typedef _Return_type_success_(return==ERROR_SUCCESS) LONG LSTATUS;
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;

#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall

typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE(HKEY);
struct HKEY__;
typedef struct HKEY__ *HKEY;

DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;
DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;      // HMODULEs can be used in place of HINSTANCEs
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSPRITE);
DECLARE_HANDLE(HLSURF);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
#define __int3264   __int64

typedef DWORD ACCESS_MASK;
typedef ACCESS_MASK *PACCESS_MASK;
typedef ACCESS_MASK REGSAM;

**/
