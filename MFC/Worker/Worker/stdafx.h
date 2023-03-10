
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>


// 公共数据区
// 数据文件
const CString ADMIN_DATA = _T("admin.dat");		//_T("admin.dat")
const CString WORKER_DATA = _T("worker.dat");	//_T("worker.dat")

// 员工信息 结构体
struct SWorker
{
	int number;			//工号
	TCHAR name[20];		//姓名
	double salary;		//薪资
	COleDateTime date;	//入职日期
};
// V1.0版本
struct SWorker_1
{
	UINT number;		//工号
	TCHAR name[20];		//姓名
	BOOL sex;			//性别
	double salary;		//薪资
	COleDateTime date;	//入职日期
	int graduate;		//学历
	DWORD language;		//外语
};
enum EWorker
{
	Number = 0,
	Name,
	Sex,
	Salary,
	Date,
	Graduate,
	Language
};

// 登录信息  结构体
struct SAdmin
{
	TCHAR sname[16];	//账号
	TCHAR spass[16];	//密码
	int nprior;			//权限：0 - 普通；1 - 高级
};






