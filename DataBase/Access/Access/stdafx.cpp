// stdafx.cpp : 只包括标准包含文件的源文件
// $safeprojectname$.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
/****************************************************
 * 配置C++借助ADO连接Access数据库
 *
 一、环境配置：
1、安装Access数据库（微软Office 2016中含有或者单独下载，下载地址：http://msdn.itellyou.cn/ 左侧选择应用程序一栏，注意选择下载64位，即标有X64的）；
2、安装Microsoft Access database engine 2007，它的作用暂时可理解为我们所写的程序与Access之间的沟通桥梁--“传话人”。
Microsoft Access database engine 2010（可以安装，但后面的代码是2007的，所以暂时建议使用2007）
下载地址：https://www.microsoft.com/zh-cn/download/details.aspx?id=13255
Microsoft Access database engine 2007
下载地址：https://www.microsoft.com/zh-cn/download/details.aspx?id=23734

二、建立数据库表
打开Access，
选择空白数据库，为你的数据库中表项起一个名字 如 test，
设计你的存储表格，
附：测试表格test.accdb。
 
三、程序代码
1、在你程序的stdafx.h头文件中加入
#import "C:/Program Files/Common Files/System/ADO/msado15.dll" rename("EOF","adoEOF"), rename("BOF","adoBOF")
（如果加载失败的话，去C:\program files\common files\system\ado查看是否有msado15.dll）
2、测试代码
见LinkDBForHX.cpp源文件。

 */