#pragma once
#include "../../Commons/type.h"

// 用户操作类
class CUser
{
public:
	CUser();
	virtual ~CUser();

	// 启动
	void Start();
	// 建立连接
	int Establish();
	// 登录
	bool Login();
	// 主菜单
	bool Menu();
	// 查找子菜单
	bool FindMenu();
	// 排序子菜单
	bool SortMenu();
	// 管理账户子菜单
	bool AccountMenu();
	// 账户排序子菜单
	bool AccountSortMenu();
	// 检查输入是否为纯数字
	int CheckNum();

	// 消息处理族
	bool DoBrowse();
	bool DoInsert();
	bool DoDelete();
	bool DoModify();
	//bool DoFindin();
	bool DoSort(int serial);

	bool DoFindNumber();	//具有唯一性
	bool DoFindName();		//可能存在多个
	bool DoFindSex();		//基本为多个
	bool DoFindSalary();	//根据薪资范围
	// ...
	bool DoFindAge();		//根据年龄范围
	bool DoFindPhone();		//具有唯一性 char[]
	bool DoFindIdcard();	//具有唯一性 char[]
	bool DoFindHome();		//模糊

	bool DoChangePassword();	//修改账户密码
	bool DoBrowseAccount();
	bool DoInsertAccount();
	bool DoDeleteAccount();
	bool DoModifyAccount();
	bool DoFindinAccount();

	bool DoSortAccount(int serial);

	bool InputData(vector<DATA>& vecdata);
	bool InputAccount(list<ACCOUNT>& listacc);
	void ModifyData(DATA& data, int field);
	void ModifyAccount(ACCOUNT& data, int field);
	bool FindData(int number, bool show = true, PDATA out_data = nullptr);
	bool FindAccount(const char* username, bool show = true, PACCOUNT out_acc = nullptr);
	//对于字符串类型查找的增强
	bool ExDoFindChars(const char* hint, int type, const char* status);

	// 清空输入缓冲区
	void CinClear();
	// 显示操作状态
	bool ShowStatus(const char* success, const char* failure);
	
	// 颜色设置
	void ColorSet();

private:
	CSocketNet m_socketClient;	//客户端Socket对象
	ACCOUNT m_account;			//登录账户
};

