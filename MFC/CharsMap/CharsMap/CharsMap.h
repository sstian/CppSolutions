/*
 开发时间：2019.04.10 15:30 - 2019.04.13 15:46
 软件名称：CharsMap 字符映射码
 设计作者：Sears Saint Tian - 田继辉 (st.tian@foxmail.com)
 开发环境：Microsoft Visual Studio Professional 2017 version 15.9.7 & MFC SDI
 环境参数：Windows SDK 版本 - 10.0.17763.0
 附加说明：因为搜狗拼音/QQ拼音输入法会更改系统默认EUDC字体路径，本程序只针对安装的搜狗拼音输入法
 帮助说明：若要恢复本地文件至初始状态，请双击程序目录下的批处理命令"Recovery.bat"

 设计流程：
 1. 界面设计 2019.04.10
 2. 字符编码 2019.04.11
 3. 输入输出 2019.04.12
 4. 明密互译  - 2019.04.12 17:44
 5. 读写文件  - 2019.04.12 17:44 SDI框架自动处理，修改IDR_MAINFRAME String Table 可自定义扩展名
 6. 配置参数  - 2019.04.12 21:36 使在另一台电脑上使用，复制字库，存在搜狗拼音输入法更改注册表系统默认路径的问题
 7. 附加图形  - 2019.04.13 02:12 慢动作绘制奥利哈刚结界，调试到了半夜，困得要死，头眼发昏，思维迟钝，CArray越界，[]却不检查
 8. 优化调整  - 2019.04.13 15:46 定时器触发优化调整线条的慢动作显示与数组越界检查
*/
// CharsMap.h: CharsMap 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CCharsMapApp:
// 有关此类的实现，请参阅 CharsMap.cpp
//

class CCharsMapApp : public CWinAppEx
{
public:
	CCharsMapApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCharsMapApp theApp;
