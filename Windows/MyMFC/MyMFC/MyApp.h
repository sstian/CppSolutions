// Win32 转为 MFC：
//0.新建->项目->Windows桌面应用程序，删除WinMain()所在的程序文件
//1.从CWinApp派生一个应用程序类 (eg. class MyApp : public CWinApp)
//2.使用派生类定义全局变量 (eg. MyApp theApp;)
//3.在预定义头文件"stdafx.h"中禁用"windows.h"，取而代之以afx开头的头文件 (eg. <afxwin.h> <afxext.h>)
//4.更改项目属性为：常规 | MFC的使用：“在静态库中使用MFC”
//5.在派生类中重写virtual BOOL InitInstance()，以此作为程序启动主函数
//6.后续过程，一个对话框资源关联到继承自CDialogEx的类

#pragma once
#include "resource.h"

class MyApp : public CWinApp
{
public:
	MyApp();
	virtual ~MyApp();

	virtual BOOL InitInstance();
};

extern MyApp theApp;

