// 代码名称：精确到微秒的延时类（基于多媒体定时器）
// 代码编写：yangw80 <yw80@qq.com>
// 最后修改：2011-5-4
// 　　　　　2013-11-2 修改为静态调用
//
/***
理想的延时：函数会将程序的执行时间部分考虑进去以实现很均匀的延时；
		必须要从上次的延时结束开始计算。
使用方法：将以上代码拷贝到新建的 MMTimer.h 中，
		然后在主程序中加上 #include "MMTimer.h"，
		在需要 Sleep 的地方执行 MMTimer::Sleep 方法。
*/
#pragma once
#include <windows.h>

class MMTimer
{
private:
	static LARGE_INTEGER m_clk;			// 保存时钟信息
	static LONGLONG m_oldclk;			// 保存开始时钟和结束时钟
	static int m_freq;					// 时钟频率(时钟时间换算率)，时间差

public:
	static void Sleep(int ms);
};

LARGE_INTEGER MMTimer::m_clk;
LONGLONG MMTimer::m_oldclk;
int MMTimer::m_freq = 0;

// 延时
void MMTimer::Sleep(int ms)
{
	if (m_oldclk == 0)
	{
		QueryPerformanceFrequency(&m_clk);
		m_freq = (int)m_clk.QuadPart / 1000;	// 获得计数器的时钟频率

												// 开始计时
		QueryPerformanceCounter(&m_clk);
		m_oldclk = m_clk.QuadPart;				// 获得开始时钟
	}

	unsigned int c = ms * m_freq;

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)
		m_oldclk = m_clk.QuadPart;
	else
		do
		{
			::Sleep(1);
			QueryPerformanceCounter(&m_clk);	// 获得终止时钟
		} while (m_clk.QuadPart < m_oldclk);
}
