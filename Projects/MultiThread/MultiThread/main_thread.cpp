/*
	2018.12.11 21:07 - 22:07
	线程的创建与使用：
	1. _beginthreadex()/_endthreadex(); 2. CreateThread(); 3. C++11 thread, 加锁解锁 mutex
*/
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <thread>
#include <mutex>
using namespace std;

unsigned __stdcall ThreadFunc(void* arglist)
{
	int arg = *(int*)arglist;
	wcout << "ThreadFunc: " << arg << endl;
	_endthreadex(0);	//结束线程
	return 1;
}

DWORD WINAPI ThreadFunc2(LPVOID lpThreadParameter)
{
	int arg = *(int*)lpThreadParameter;
	wcout << "ThreadFunc2: " << arg << endl;
	return 0;
}
// C++11 thread
bool ThreadFunc3(int a, double b)
{
	cout << "a = " << a << " b = " << b << endl;
	return true;
}

class TestThread
{
public:
	TestThread() { temp = 0; }
	~TestThread() { }

	int ThreadFunc4(int a, double b, const char* c, bool d)
	{
		cout << "TestThread: a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;
		return 0;
	}
	void ThreadFuncRun()
	{
		thread t1(&TestThread::ThreadFunc5, this, 1);
		thread t2(&TestThread::ThreadFunc5, this, 2);
		t1.join();
		t2.join();
	}
	int ThreadFunc5(int num)
	{
		for (int count = 3; count > 0; count--)
		{
			mut.lock();
			cout << "ThreadFunc5-" << num << ": temp = " << temp++ << endl;
			mut.unlock();
		}
		return 0;
	}
private:
	volatile int temp;
	//volatile在多线程当中经常使用，因为在某一线程多次调用某一个变量，编译器会进行优化，将该变量存放在在寄存器当中，不会每次都从内存当中读入，
	//该变量同时在其他线程当中被修改就会发生脏读取错误；
	//加上volatile修饰，则会提醒编译器，这个变量可能会被改变，不能存放到寄存器当中，需要每次都从内存当中读取。
	
	static mutex mut;
	//创造的每一个线程只要在一个进程内，都是共享内存池的，加锁以防止读写数据可能会发生混乱。
};
mutex TestThread::mut;	//！似乎不能定义为成员变量

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** Thread ***" << endl;
	// 方法一.
	int threadArg = 12;			//传递的线程参数
	unsigned int threadAddr;	//接收线程地址
	HANDLE hthread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, &threadArg, 0, &threadAddr);	// 创建线程
	WaitForSingleObject(hthread, INFINITE);
	wcout << "threadAddr = " << threadAddr << endl;
	//Sleep(2000);
	
	DWORD code;
	GetExitCodeThread(hthread, &code);	//线程退出代码	/// BOOL GetExitCodeThread(_In_ HANDLE hThread,_Out_ LPDWORD lpExitCode);

	wcout << "ExitCodeThread = " << code << endl << endl;

	CloseHandle(hthread);				//关闭线程句柄	/// BOOL CloseHandle(_In_ _Post_ptr_invalid_ HANDLE hObject);

	// 方法二
	int parameter = 22;
	DWORD threadid;
	HANDLE hthread2 = CreateThread(NULL, 0, ThreadFunc2, (LPVOID)&parameter, CREATE_SUSPENDED, &threadid);
	ResumeThread(hthread2);								/// DWORD ResumeThread(_In_ HANDLE hThread);
	WaitForSingleObject(hthread2, INFINITE);			/// DWORD WaitForSingleObject(_In_ HANDLE hHandle,_In_ DWORD dwMilliseconds);
	wcout << "threadid = " << threadid << endl;
	CloseHandle(hthread2);

	// 方法三
	//1. 普通函数
	int a = 12;
	double b = 3.14;
	thread t(ThreadFunc3, a, b);	
	wcout << "thread t.get_id() = " << t.get_id() << endl;
	//t.join();		//启动子线程而阻塞主线程，当子线程运行结束后，才会继续运行主线程
	t.detach();		//启动子线程，并且让子线程和主线程分离，子线程和主线程各运行各的

	//2. 成员函数
	TestThread test;
	const char* c = "good";
	bool d = true;
	// std::thread ttest(函数(成员函数)地址，对象地址，成员函数的参数1，参数2，参数3...)
	thread ttest(&TestThread::ThreadFunc4, test, a, b, c, d);	
	wcout << "ttest.get_id() = " << ttest.get_id() << endl;
	ttest.join();

	//3. 成员函数 this，加锁解锁
	//相比非成员函数，成员函数需要给出类实例化对象的地址，
	//如果该线程是在同一类的某一成员函数当中被构造，则直接用this关键字代替即可
	TestThread testmux;
	testmux.ThreadFuncRun();

	system("pause");
	return 0;
}

/*== 在VS2017运行结果：==
*** Thread ***
ThreadFunc: 12
threadAddr = 3164
ExitCodeThread = 0

ThreadFunc2: 22
threadid = 4160
a = 12 b = 3.14
thread t.get_id() = 220
TestThread: a = ttest.get_id() = 4708
12, b = 3.14, c = good, d = 1
ThreadFunc5-1: temp = 0
ThreadFunc5-1: temp = 1
ThreadFunc5-2: temp = 2
ThreadFunc5-2: temp = 3
ThreadFunc5-2: temp = 4
ThreadFunc5-1: temp = 5
请按任意键继续. . .
*/

/***
// 方法一
#ifdef _WIN64
	typedef unsigned __int64  uintptr_t;
#else
	typedef unsigned int uintptr_t;

typedef unsigned (__stdcall* _beginthreadex_proc_type)(void*);

_Success_(return != 0)
uintptr_t __cdecl _beginthreadex(					////函数返回值：成功返回新线程的句柄，失败返回NULL。 
_In_opt_  void*                    _Security,		//线程内核对象的安全属性，一般传入NULL表示使用默认设置
_In_      unsigned                 _StackSize,		//线程栈空间大小，传入0表示使用默认大小（1MB）
_In_      _beginthreadex_proc_type _StartAddress,	//新线程所执行的线程函数地址，多个线程可以使用同一个函数地址
_In_opt_  void*                    _ArgList,		//传给线程函数的参数
_In_      unsigned                 _InitFlag,		//控制线程的创建：0-线程创建后立即调度；CREATE_SUSPENDED-线程创建后暂停运行，直到调用ResumeThread()
_Out_opt_ unsigned*                _ThrdAddr		//返回线程的ID号，传入NULL表示不需要返回该线程ID号
);

void __cdecl _endthreadex(
_In_ unsigned _ReturnCode
);

// 方法二
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

HANDLE WINAPI CreateThread(
_In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
_In_      SIZE_T                 dwStackSize,
_In_      LPTHREAD_START_ROUTINE lpStartAddress,
_In_opt_  LPVOID                 lpParameter,
_In_      DWORD                  dwCreationFlags,
_Out_opt_ LPDWORD                lpThreadId
);
*/