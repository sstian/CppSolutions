/*
	2020.06.04 10:32 - 14:22
	glogtest - Google's glog test
配置与使用：
1. CMake编译生成glog：Release x64
	项目 属性 | 配置属性：
	常规 | 配置类型 - 静态库(.lib)，字符集 - 使用 Unicode 字符集
	C/C++ | 代码生成 | 运行库 - 多线程 (/MT)
2. 新建项目：glogtest，Debug/Release x64
	项目 属性 | 配置属性：
	常规 | 配置类型 - 应用程序(.exe)，字符集 - 使用 Unicode 字符集
	C/C++ | 代码生成 | 运行库 - 多线程 (/MT)
	C/C++ | 代码生成 | 预处理器 | 预处理器定义 - <编辑...>: 
WIN32
_WINDOWS
NDEBUG
GLOG_NO_ABBREVIATED_SEVERITIES
GOOGLE_GLOG_DLL_DECL=
3. 复制文件到glogtest项目目录下：
	生成的 glog.lib
	原始目录中的 D:\Program Files\glog\glog-master\src\windows\glog 目录

说明：
	1. 日志级别：INFO, WARNING, ERROR, FATAL 对应 0，1，2，3
	2. glog不支持宽字符 wchar/wstring, 因为 ostream 重载 << 为 char
	3. 文件格式：<program name>.<hostname>.<user name>.log.<severity level>.<date>-<time>.<pid>
		e.g. glogtest.exe.SNOW-ANGEL.Snow-Angel.log.INFO.log_20200604-142327.8296
	4. Log line format: [IWEF]yyyymmdd hh:mm:ss.uuuuuu threadid file:line] msg
		e.g. I20200604 14:23:27.519625  2012 main_glogtest.cpp:59] info test hello log!
*/

#include "glog/logging.h"
using namespace google;

#pragma comment(lib, "glog.lib")

int main(int argc, char* argv[])
{
	// Set Flags
	FLAGS_log_dir = "D:\\Logs";					// Set log directory
	FLAGS_colorlogtostderr = true;				// Set log color
	FLAGS_logbufsecs = 0;						// Set log output speed(s)
	FLAGS_max_log_size = 1024;					// Set max log file size
	FLAGS_stop_logging_if_full_disk = true;		// If disk is full, stop logging

	// Start google log system
	// e.g. 只修改了INFO级别的文件名：INFO_log_20200604-135229.13088
	google::InitGoogleLogging(argv[0]);
	google::SetLogDestination(google::GLOG_INFO, (std::string(FLAGS_log_dir) + "\\INFO_").c_str());
	google::SetLogFilenameExtension("log_");
	google::SetStderrLogging(google::GLOG_INFO);
	
	//clock_t start, end;
	//start = clock();

	// 1. Output logs
	char sz[20] = "char[] - hello log!";
	std::string str = "string - hello log!";
	LOG(INFO) << sz;
	LOG(INFO) << str;
	LOG(INFO) << "info test" << " hello log!";	//output a Info log
	LOG(WARNING) << "warning test";				//output a Warning log
	LOG(ERROR) << "error test";					//output a Error log
	//LOG(FATAL) << "fatal test";					//output a Fatal log, exe exit!

	// 2. 按条件/次数打印日志
	for (int i = 1; i <= 20; i++)
	{
		LOG(INFO) << "info test " << i;	//output a Info log

		// 在满足一定条件时打印日志：i > 10
		LOG_IF(INFO, i > 10) << "LOG_IF: Got lots of cookies " << i;

		// 在执行的第1、11、21、...次时打印日志
		// google::COUNTER 用来表示是哪一次执行
		LOG_EVERY_N(INFO, 10) << "LOG_EVERY_N: " << google::COUNTER << "th cookie";

		// 合并，LOG_IF_EVERY_N = LOG_IF + LOG_EVERY_N
		LOG_IF_EVERY_N(INFO, (i > 10), 10) << "LOG_IF_EVERY_N: Got the " 
			<< google::COUNTER << "th big cookie";

		// 在执行的前10次打印日志
		LOG_FIRST_N(INFO, 10) << "LOG_FIRST_N: " << google::COUNTER << "th cookie";
	}

	google::ShutdownGoogleLogging();

	//end = clock();
	//double pass = (double)(end - start) / CLOCKS_PER_SEC;
	//LOG(INFO) << "time = " << pass << " s";

	system("pause");
	return 0;
}

/*** vs2017 output:
I20200604 14:23:27.509634  2012 main_glogtest.cpp:57] char[] - hello log!
I20200604 14:23:27.519625  2012 main_glogtest.cpp:58] string - hello log!
I20200604 14:23:27.519625  2012 main_glogtest.cpp:59] info test hello log!
W20200604 14:23:27.519625  2012 main_glogtest.cpp:60] warning test
E20200604 14:23:27.522624  2012 main_glogtest.cpp:61] error test
I20200604 14:23:27.523624  2012 main_glogtest.cpp:67] info test 1
I20200604 14:23:27.524623  2012 main_glogtest.cpp:74] LOG_EVERY_N: 1th cookie
I20200604 14:23:27.524623  2012 main_glogtest.cpp:81] LOG_FIRST_N: 1th cookie
I20200604 14:23:27.524623  2012 main_glogtest.cpp:67] info test 2
I20200604 14:23:27.525622  2012 main_glogtest.cpp:81] LOG_FIRST_N: 2th cookie
I20200604 14:23:27.525622  2012 main_glogtest.cpp:67] info test 3
I20200604 14:23:27.525622  2012 main_glogtest.cpp:81] LOG_FIRST_N: 3th cookie
I20200604 14:23:27.525622  2012 main_glogtest.cpp:67] info test 4
I20200604 14:23:27.526625  2012 main_glogtest.cpp:81] LOG_FIRST_N: 4th cookie
I20200604 14:23:27.526625  2012 main_glogtest.cpp:67] info test 5
I20200604 14:23:27.526625  2012 main_glogtest.cpp:81] LOG_FIRST_N: 5th cookie
I20200604 14:23:27.526625  2012 main_glogtest.cpp:67] info test 6
I20200604 14:23:27.526625  2012 main_glogtest.cpp:81] LOG_FIRST_N: 6th cookie
I20200604 14:23:27.527621  2012 main_glogtest.cpp:67] info test 7
I20200604 14:23:27.527621  2012 main_glogtest.cpp:81] LOG_FIRST_N: 7th cookie
I20200604 14:23:27.527621  2012 main_glogtest.cpp:67] info test 8
I20200604 14:23:27.527621  2012 main_glogtest.cpp:81] LOG_FIRST_N: 8th cookie
I20200604 14:23:27.527621  2012 main_glogtest.cpp:67] info test 9
I20200604 14:23:27.530619  2012 main_glogtest.cpp:81] LOG_FIRST_N: 9th cookie
I20200604 14:23:27.530619  2012 main_glogtest.cpp:67] info test 10
I20200604 14:23:27.530619  2012 main_glogtest.cpp:81] LOG_FIRST_N: 10th cookie
I20200604 14:23:27.530619  2012 main_glogtest.cpp:67] info test 11
I20200604 14:23:27.531618  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 11
I20200604 14:23:27.531618  2012 main_glogtest.cpp:74] LOG_EVERY_N: 11th cookie
I20200604 14:23:27.531618  2012 main_glogtest.cpp:77] LOG_IF_EVERY_N: Got the 11th big cookie
I20200604 14:23:27.531618  2012 main_glogtest.cpp:67] info test 12
I20200604 14:23:27.532618  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 12
I20200604 14:23:27.533617  2012 main_glogtest.cpp:67] info test 13
I20200604 14:23:27.533617  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 13
I20200604 14:23:27.536614  2012 main_glogtest.cpp:67] info test 14
I20200604 14:23:27.537614  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 14
I20200604 14:23:27.538614  2012 main_glogtest.cpp:67] info test 15
I20200604 14:23:27.541612  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 15
I20200604 14:23:27.541612  2012 main_glogtest.cpp:67] info test 16
I20200604 14:23:27.543617  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 16
I20200604 14:23:27.544610  2012 main_glogtest.cpp:67] info test 17
I20200604 14:23:27.545609  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 17
I20200604 14:23:27.546609  2012 main_glogtest.cpp:67] info test 18
I20200604 14:23:27.546609  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 18
I20200604 14:23:27.547608  2012 main_glogtest.cpp:67] info test 19
I20200604 14:23:27.548607  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 19
I20200604 14:23:27.550609  2012 main_glogtest.cpp:67] info test 20
I20200604 14:23:27.552606  2012 main_glogtest.cpp:70] LOG_IF: Got lots of cookies 20
请按任意键继续. . .请按任意键继续. . .

***/