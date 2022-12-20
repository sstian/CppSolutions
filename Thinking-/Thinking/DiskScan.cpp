/*  2017.9.28 14:28
	磁盘扫描、文件遍历
*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <io.h>
using namespace std;

bool IsDirectoy(unsigned int attrib);
void PrintFile(const char* path);
void ScanFile(const char* path, int tab = 0);
bool SearchFile(const char* path, const char* file);
int main()
{
	PrintFile("E:\\360Downloads\\开发环境\\OpenCV\\OpenCV入门教程.pdf");
	ScanFile("E:\\360Downloads");
	SearchFile("E:\\360Downloads", "OpenCV入门教程.pdf");
	return 0;
}

bool IsDirectoy(unsigned int attrib)
{
	return (attrib & _A_SUBDIR);
}

/* 打印文件属性信息 
filespec: 文件路径及文件名 */
void PrintFile(const char* filespec)
{
	struct _finddata_t fileData;	//文件信息
	intptr_t fileHandle;			//文件句柄
	char buffer[30];	//接收文件时间数据
	//cout << "Please input the directory of file:\n";
	//cin >> filespec;
	if (-1 == (fileHandle = _findfirst(filespec, &fileData)))	// intptr_t _findfirst(const char *filespec, struct _finddata_t *fileinfo);
		cout << "No such file in current directory!" << endl;
	else
	{
		cout << "****** File lists ******\n";
		cout << "NOR RDO HID SYS ARC DIR"
			<< setiosflags(ios::left) << setw(30) << " FILE"
			<< setiosflags(ios::left) << setw(10) << " SIZE"
			<< " DATE" << endl;
		do
		{
			cout << (fileData.attrib & _A_NORMAL ? "***" : "---") << " "
				<< (fileData.attrib & _A_RDONLY ? "***" : "---") << " "
				<< (fileData.attrib & _A_HIDDEN ? "***" : "---") << " "
				<< (fileData.attrib & _A_SYSTEM ? "***" : "---") << " "
				<< (fileData.attrib & _A_ARCH ? "***" : "---") << " "
				<< (fileData.attrib & _A_SUBDIR ? "+++" : "---") << " ";
			ctime_s(buffer, _countof(buffer), &fileData.time_write);	// errno_t ctime_s(char* buffer, size_t numberOfElements, const time_t *time);
			cout << setiosflags(ios::left) << setw(30) << fileData.name
				<< setiosflags(ios::left) << setw(10) << fileData.size
				<< buffer << endl;
		} while (0 == _findnext(fileHandle, &fileData));	// int _findnext(intptr_t handle, struct _finddata_t *fileinfo);
	}
	_findclose(fileHandle);	// int _findclose(intptr_t _FindHandle);
}

/* 文件遍历 
path: 文件路径；tab: 控制缩进 */
void ScanFile(const char* path, int tab)
{
	char filespec[255];	//文件目录
	char sdir[255];		//子目录
	strcpy_s(filespec, path);
	strcat_s(filespec, "\\*.*");
	struct _finddata_t fileData;	//文件信息
	intptr_t fileHandle;			//文件句柄
	if (-1 == (fileHandle = _findfirst(filespec, &fileData)))	// intptr_t _findfirst(const char *filespec, struct _finddata_t *fileinfo);
	{
		cout << "No such file directory." << endl;
		return;
	}
	else
	{
		do
		{
			if (IsDirectoy(fileData.attrib))
			{
				if (strcmp(fileData.name, ".") && strcmp(fileData.name, ".."))		//除去目录“.”和“..”
				{
					for (int i = 0; i < tab; i++)
						cout << "   ";
					cout << "++ " << fileData.name << endl;
					strcpy_s(sdir, path);
					strcat_s(sdir, "\\");
					strcat_s(sdir, fileData.name);
					ScanFile(sdir, tab + 1);
				}
			}
			else
			{
				for (int i = 0; i < tab; i++)
					cout << "   ";
				cout << "   " << fileData.name << "  " << fileData.size << endl;
			}
		} while (0 == _findnext(fileHandle, &fileData));
	}
	_findclose(fileHandle);
}

/* 文件搜索 
path: 路径；file: 要搜索的文件名*/
bool SearchFile(const char* path, const char* file)
{
	char filespec[255];	//文件目录
	char sdir[255];		//子目录
	strcpy_s(filespec, path);
	strcat_s(filespec, "\\*.*");
	struct _finddata_t fileData;	//文件信息
	intptr_t fileHandle;			//文件句柄
	if (-1 == (fileHandle = _findfirst(filespec, &fileData)))	// intptr_t _findfirst(const char *filespec, struct _finddata_t *fileinfo);
	{
		cout << "No such file directory." << endl;
		return false;
	}
	else
	{
		do 
		{
			if (!strcmp(fileData.name, file))
			{
				cout << filespec << "\b\b\b" << fileData.name << endl;
				return true;
			}
			else
				if (IsDirectoy(fileData.attrib))
				{
					if (strcmp(fileData.name, ".") && strcmp(fileData.name, ".."))		//除去目录“.”和“..”
					{
						strcpy_s(sdir, path);
						strcat_s(sdir, "\\");
						strcat_s(sdir, fileData.name);
						SearchFile(sdir, file);
					}
				}
		} while (0 == _findnext(fileHandle, &fileData));
	}
	return false;
}
/*********************************************************************************
typedef int              intptr_t;

#define _finddata_t     _finddata64i32_t
struct _finddata64i32_t
{
unsigned    attrib;
__time64_t  time_create;    // -1 for FAT file systems
__time64_t  time_access;    // -1 for FAT file systems
__time64_t  time_write;
_fsize_t    size;
char        name[260];
};
typedef int                           errno_t;
typedef __int64                       __time64_t;
typedef unsigned long _fsize_t;


// File attribute constants for the _findfirst() family of functions
#define _A_NORMAL 0x00 // Normal file - No read/write restrictions
#define _A_RDONLY 0x01 // Read only file
#define _A_HIDDEN 0x02 // Hidden file
#define _A_SYSTEM 0x04 // System file
#define _A_SUBDIR 0x10 // Subdirectory
#define _A_ARCH   0x20 // Archive file

#define _countof __crt_countof

**********************************************************************************/