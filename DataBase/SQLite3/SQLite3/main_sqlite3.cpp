/*
	2019.04.26 14:16
	C++ 连接 SQLite 3.28.0
*/
#include <iostream>
#include "sqlite3.h"				//头文件

using namespace std;

#pragma comment(lib, "sqlite3.lib")	//静态链接库

// 回调函数，每次结果记录都调用一次
static int callback(void* data, int argc, char** argv, char** azColName);
// 打开数据库
int OpenDatabase(const char* filename, sqlite3** db);
// 创建数据表
int CreateTable(sqlite3* db, const char* sql = nullptr);
// 增加数据
int InsertIntoTable(sqlite3* db, const char* sql = nullptr);
// 删除数据
int DeleteFromTable(sqlite3* db, const char* sql = nullptr);
// 修改数据
int UpdateTableSet(sqlite3* db, const char* sql = nullptr);
// 查找数据
int SelectThingTable(sqlite3* db, const char* sql = nullptr);

int main(int argc, char* argv[])
{
	sqlite3 * db;					//数据库指针
	const char* sql = nullptr;		//SQL 语句

	// Open database
	OpenDatabase("snowflake.db", &db);
	// Create Table SQL statement
	CreateTable(db, nullptr);

	// Insert Into Table SQL statement
	InsertIntoTable(db, nullptr);
	SelectThingTable(db, nullptr);

	// Delete From Table SQL statement
	DeleteFromTable(db, nullptr);
	SelectThingTable(db, nullptr);

	// Update Table SQL statement
	UpdateTableSet(db, nullptr);
	SelectThingTable(db, nullptr);

	//// Select Table SQL statement
	//SelectThingTable(db, nullptr);

	// Close database
	sqlite3_close(db);

	system("pause");
	return 0;
}

int callback(void * data, int argc, char ** argv, char ** azColName)
{
	//cout << static_cast<const char*>(data) << endl;
	//cout << "argc = " << argc << endl;
	for (int index = 0; index < argc; index++)
	{
		//cout << azColName[index] << " = " << (argv[index] ? argv[index] : "NULL") << endl;
		cout << (argv[index] ? argv[index] : "NULL") << "\t";
	}
	cout << endl;
	return 0;
}

int OpenDatabase(const char * filename, sqlite3 ** db)
{
	int res = sqlite3_open(filename, db);
	if (SQLITE_OK == res)
	{
		cout << "Open database succeed." << endl;
	}
	else
	{
		cout << "Can't open database: " << sqlite3_errmsg(*db) << endl;
		exit(1);
	}
	return res;
}

int CreateTable(sqlite3 * db, const char * sql)
{
	sql = "CREATE TABLE company("  \
		"id INT PRIMARY KEY     NOT NULL, " \
		"name           TEXT    NOT NULL, " \
		"age            INT     NOT NULL, " \
		"address        CHAR(50), " \
		"salary         REAL );";

	// Execute SQL statement
	char* errmsg = nullptr;
	int res = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (SQLITE_OK == res)
	{
		cout << "Create table succeed.\n" << endl;
	}
	else
	{
		cout << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	return res;
}

int InsertIntoTable(sqlite3 * db, const char * sql)
{
	sql = "INSERT INTO company (id, name, age, address, salary) "  \
		"VALUES (1, 'Paul', 32, 'China', 20000.00 ); " \
		"INSERT INTO company (id, name, age, address, salary) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO company (id, name, age, address, salary) " \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO company (id, name, age, address, salary) " \
		"VALUES (4, 'Mark', 25, 'Tokyo', 20000.00 );";

	// Execute SQL statement
	char* errmsg = nullptr;
	int res = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (SQLITE_OK == res)
	{
		cout << "Insert into table succeed.\n" << endl;
	}
	else
	{
		cout << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	return res;
}

int DeleteFromTable(sqlite3 * db, const char * sql)
{
	sql = "DELETE FROM company WHERE ID = 1;";

	// Execute SQL statement
	char* errmsg = nullptr;
	int res = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (SQLITE_OK == res)
	{
		cout << "Delete from table succeed.\n" << endl;
	}
	else
	{
		cout << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	return res;

}

int UpdateTableSet(sqlite3 * db, const char * sql)
{
	sql = "UPDATE company SET salary = 55000.00 WHERE ID = 2; ";

	// Execute SQL statement
	char* errmsg = nullptr;
	int res = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (SQLITE_OK == res)
	{
		cout << "Update table succeed.\n" << endl;
	}
	else
	{
		cout << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	return res;
}

int SelectThingTable(sqlite3 * db, const char * sql)
{
	sql = "SELECT * FROM company";

	// Execute SQL statement
	char* errmsg = nullptr;
	const char* data = "Callback function called: ";
	cout << "id\tname\tage\taddress\tsalary\n";
	int res = sqlite3_exec(db, sql, callback, (void*)data, &errmsg);
	if (SQLITE_OK == res)
	{
		cout << "Select from table succeed.\n" << endl;
	}
	else
	{
		cout << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	return res;
}

/** 在VS2017中运行结果：
Open database succeed.
Create table succeed.

Insert into table succeed.

id      name    age     address salary
1       Paul    32      China   20000.0
2       Allen   25      Texas   15000.0
3       Teddy   23      Norway  20000.0
4       Mark    25      Tokyo   20000.0
Select from table succeed.

Delete from table succeed.

id      name    age     address salary
2       Allen   25      Texas   15000.0
3       Teddy   23      Norway  20000.0
4       Mark    25      Tokyo   20000.0
Select from table succeed.

Update table succeed.

id      name    age     address salary
2       Allen   25      Texas   55000.0
3       Teddy   23      Norway  20000.0
4       Mark    25      Tokyo   20000.0
Select from table succeed.

请按任意键继续. . .
**/