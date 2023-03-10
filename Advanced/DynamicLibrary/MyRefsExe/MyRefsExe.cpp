//动态链接库使用的程序文件
// 动态链接库的创建和使用：
//方案一：多个项目在一个解决方案下（**推荐：方便管理）
//0. 新建空项目 (eg. DynamicLibrary)，删除默认工程
//1. 解决方案 | (右键点击) | 添加... | 新建项目... (eg. MathFuncsDll)，添加类的.h和.cpp文件 (eg. MathFuncsDll.h/.cpp | MyMathFuncs)，定义描述符和类，如：
//#ifdef MATHFUNCSDLL_EXPORTS
//#define MATHFUNCSDLL_API __declspec(dllexport) 
//#else
//#define MATHFUNCSDLL_API __declspec(dllimport) 
//#endif
//class MATHFUNCSDLL_API MyMathFuncs{};
//   修改项目属性：C/C++ | 预处理器 | 预处理定义 - 添加宏 (eg. MATHFUNCSDLL_EXPORTS)，常规 | 配置类型 - 动态库(.dll)
//2. 右键生成，则会在项目目录下产生.dll和.lib文件 (eg. MathFuncsDll.dll, MathFuncsDll.lib)
//3. 同理，解决方案 | (右键点击) | 添加... | 新建项目... (eg. MyRefsExe)，添加动态链接库使用的程序文件 (eg. MyRefsExe.cpp)
//4. 引用链接库：
//   方法(1)，引用(右击) | 添加引用... | 项目 | 解决方案 - 勾选确定；（**推荐：解决模块x86与x64匹配问题）
//   方法(2)，资源文件(右击) | 添加 | 现有项... - 找到.lib文件 (eg. MathFuncsDll.lib)
//5. 设为启动项目，调试 | 开始执行(不调试)
//
//方案二：解决方案与项目匹配，项目分开
//将生成的.dll, .lib和.h文件拷贝到运行项目目录下，引用连接库即可 (eg. MathFuncsDll.dll, MathFuncsDll.lib, MathFuncsDll.h) 

#include <iostream>
#include <cstdlib>
#include "../MathFuncsDll/MathFuncsDll.h"  //包含数学模型动态链接库头文件
// ..表示父级目录；.表示当前目录
using namespace std;

int main(void)
{
	double a = 13.4;
	double b = 2.0;

	cout << "a = " << a << "\n"
		<< "b = " << b << endl;
	// 一、命名空间
	//cout << "a + b = " <<
	//	MathFuncs::MyMathFuncs::Add(a, b) << endl;
	//cout << "a - b = " <<
	//	MathFuncs::MyMathFuncs::Subtract(a, b) << endl;
	//cout << "a * b = " <<
	//	MathFuncs::MyMathFuncs::Multiply(a, b) << endl;
	//cout << "a / b = " <<
	//	MathFuncs::MyMathFuncs::Divide(a, b) << endl;
	//cout << "a / 0 = " << endl;
	//try
	//{	//对于可能出现异常的语句块进行try一下
	//	cout << MathFuncs::MyMathFuncs::Divide(a, 0) << endl;
	//}
	//catch (const invalid_argument& e)
	//{
	//	cout << "Caught exception: " << e.what() << endl;
	//}

	// 二、类 全局函数
	cout << "a + b = " <<
		MyMathFuncs::Add(a, b) << endl;
	cout << "a - b = " <<
		MyMathFuncs::Subtract(a, b) << endl;
	cout << "a * b = " <<
		MyMathFuncs::Multiply(a, b) << endl;
	cout << "a / b = " <<
		MyMathFuncs::Divide(a, b) << endl;
	cout << "a / 0 = " << endl;
	try
	{	//对于可能出现异常的语句块进行try一下
		cout << MyMathFuncs::Divide(a, 0) << endl;
	}
	catch (const invalid_argument& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}
	cout << "29 % 10 = " <<
		Mode(29) << endl;

	system("pause");
	return 0;
}