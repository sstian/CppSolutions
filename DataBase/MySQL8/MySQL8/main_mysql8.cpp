/*
	2018.04.26 16:32
	C++ 连接 MySQL 8.0.15
	项目属性 | 配置属性 | VC++目录 |
	包含目录：C:\Program Files\MySQL\MySQL Server 8.0\include
	库目录：C : \Program Files\MySQL\MySQL Server 8.0\lib
*/
#include <iostream>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")
using namespace std;

// 函数声明
// 连接数据库
void ConnectDatabase(MYSQL& mysql);
// 增删改查
bool InsertData(MYSQL& mysql, const char* sql);
bool DeleteData(MYSQL& mysql, const char* sql);
bool ModifyData(MYSQL& mysql, const char* sql);
bool QueryData(MYSQL& mysql, const char* sql);

int main(int argc, char* argv[])
{
	MYSQL mysql;		//数据库结构体
	
	ConnectDatabase(mysql);
	QueryData(mysql, nullptr);
	InsertData(mysql, nullptr);
	QueryData(mysql, nullptr);
	ModifyData(mysql, nullptr);
	QueryData(mysql, nullptr);
	DeleteData(mysql, nullptr);
	QueryData(mysql, nullptr);

	// 关闭数据库
	mysql_close(&mysql);

	system("pause");
	return 0;
}


void ConnectDatabase(MYSQL & mysql)
{
	// 初始化数据库
	mysql_init(&mysql);
	// 设置编码方式
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "GBK");
	// 连接数据库
	if (!mysql_real_connect(&mysql, "localhost", "root", "5200", "student", 3306, nullptr, 0))
	{
		cout << "Connect database failed! Error: " << mysql_error(&mysql) << endl;
		system("pause");
		exit(1);
	}
	else
	{
		cout << "Connect database succeed." << endl;
	}

}

bool InsertData(MYSQL & mysql, const char * sql)
{
	sql = "INSERT INTO info (id, name, address) VALUES (2020, 'Lu', 'Anhui');";
	int query = mysql_query(&mysql, sql);
	if (query)
	{
		cout << "Insert data failed! Error: " << mysql_error(&mysql) << endl;
		return false;
	}
	else
	{
		cout << "Insert data succeed." << endl;
	}
	return true;
}

bool DeleteData(MYSQL & mysql, const char * sql)
{
	sql = "DELETE FROM info WHERE id = 2020;";
	int query = mysql_query(&mysql, sql);
	if (query)
	{
		cout << "Delete data failed! Error: " << mysql_error(&mysql) << endl;
		return false;
	}
	else
	{
		cout << "Delete data succeed." << endl;
	}
	return true;
}

bool ModifyData(MYSQL & mysql, const char * sql)
{
	sql = "UPDATE info SET name = 'KUN' WHERE id = 2020;";
	int query = mysql_query(&mysql, sql);
	if (query)
	{
		cout << "Modify data failed! Error: " << mysql_error(&mysql) << endl;
		return false;
	}
	else
	{
		cout << "Modify data succeed." << endl;
	}
	return true;
}

bool QueryData(MYSQL & mysql, const char * sql)
{
	MYSQL_RES* res;		//结果集结构体
	MYSQL_FIELD* field;	//字段名
	MYSQL_ROW row;		//char** 二维数组，存放记录

	// 查询数据，返回0查询成功，返回1查询失败
	sql = "SELECT * FROM info;";
	int query = mysql_query(&mysql, sql);
	if (query)
	{
		cout << "Query data failed! Error: " << mysql_error(&mysql) << endl;
		return false;
	}
	else
	{
		cout << "Query data succeed." << endl;
	}
	// 获取结果集
	res = mysql_store_result(&mysql);
	// 输出数据行数
	cout << "The number of dataline returned : " << mysql_affected_rows(&mysql) << endl;
	// 获取字段名
	while (field = mysql_fetch_field(res))
	{
		cout << field->name << "\t";
	}
	cout << endl;
	// 获取记录
	while (row = mysql_fetch_row(res))
	{
		cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
	}
	cout << endl;
	// 释放结果集
	mysql_free_result(res);

	return true;
}

/**
typedef struct MYSQL {
	NET net;						// Communication parameters
	unsigned char *connector_fd;	// ConnectorFd for SSL
	char *host, *user, *passwd, *unix_socket, *server_version, *host_info;
	char *info, *db;
	struct CHARSET_INFO *charset;
	MYSQL_FIELD *fields;
	struct MEM_ROOT *field_alloc;
	my_ulonglong affected_rows;
	my_ulonglong insert_id;			// id if insert on table with NEXTNR
	my_ulonglong extra_info;		// Not used
	unsigned long thread_id;		//Id for connection in server
	unsigned long packet_length;
	unsigned int port;
	unsigned long client_flag, server_capabilities;
	unsigned int protocol_version;
	unsigned int field_count;
	unsigned int server_status;
	unsigned int server_language;
	unsigned int warning_count;
	struct st_mysql_options options;
	enum mysql_status status;
	enum enum_resultset_metadata resultset_metadata;
	bool free_me;					// If free in mysql_close
	bool reconnect;					// set to 1 if automatic reconnect
	char scramble[SCRAMBLE_LENGTH + 1];		// session-wide random string
	LIST *stmts;							// list of all statements
	const struct MYSQL_METHODS *methods;
	void *thd;
	bool *unbuffered_fetch_owner;
	void *extension;
} MYSQL;

typedef struct MYSQL_RES {
	my_ulonglong row_count;
	MYSQL_FIELD *fields;
	struct MYSQL_DATA *data;
	MYSQL_ROWS *data_cursor;
	unsigned long *lengths;		// column lengths of current row
	MYSQL *handle;				// for unbuffered reads
	const struct MYSQL_METHODS *methods;
	MYSQL_ROW row;				// If unbuffered read
	MYSQL_ROW current_row;		// buffer to current row
	struct MEM_ROOT *field_alloc;
	unsigned int field_count, current_field;
	bool eof;					// Used by mysql_fetch_row
	bool unbuffered_fetch_cancelled;	// mysql_stmt_close() had to cancel this result
	enum enum_resultset_metadata metadata;
	void *extension;
} MYSQL_RES;

typedef struct MYSQL_FIELD {
	char *name;					// Name of column
	char *org_name;				// Original column name, if an alias
	char *table;				// Table of column if column was a field
	char *org_table;			// Org table name, if table was an alias
	char *db;					// Database for table
	char *catalog;				// Catalog for table
	char *def;					// Default value (set by mysql_list_fields)
	unsigned long length;		// Width of column (create length)
	unsigned long max_length;	// Max width for selected set
	unsigned int name_length;
	unsigned int org_name_length;
	unsigned int table_length;
	unsigned int org_table_length;
	unsigned int db_length;
	unsigned int catalog_length;
	unsigned int def_length;
	unsigned int flags;			// Div flags
	unsigned int decimals;		// Number of decimals in field
	unsigned int charsetnr;		// Character set
	enum enum_field_types type; // Type of field. See mysql_com.h for types
	void *extension;
} MYSQL_FIELD;

typedef char **MYSQL_ROW;                //return data as array of strings

MYSQL *STDCALL mysql_init(MYSQL *mysql);

int STDCALL mysql_options(MYSQL *mysql, enum mysql_option option, const void *arg);

MYSQL *STDCALL mysql_real_connect(MYSQL *mysql, const char *host,
	const char *user, const char *passwd,
	const char *db, unsigned int port,
	const char *unix_socket,
	unsigned long clientflag);

int STDCALL mysql_query(MYSQL *mysql, const char *q);

MYSQL_FIELD *STDCALL mysql_fetch_field(MYSQL_RES *result);

MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);

void STDCALL mysql_free_result(MYSQL_RES *result);

void STDCALL mysql_close(MYSQL *sock);

const char *STDCALL mysql_error(MYSQL *mysql);

my_ulonglong STDCALL mysql_affected_rows(MYSQL *mysql);
**/

/*** 在VS2017中运行结果：
Connect database succeed.
Query data succeed.
The number of dataline returned : 3
id      name    address
2017    Tian    Henan
2018    Wang    Shandong
2019    Li      Beijing

Insert data succeed.
Query data succeed.
The number of dataline returned : 4
id      name    address
2017    Tian    Henan
2018    Wang    Shandong
2019    Li      Beijing
2020    Lu      Anhui

Modify data succeed.
Query data succeed.
The number of dataline returned : 4
id      name    address
2017    Tian    Henan
2018    Wang    Shandong
2019    Li      Beijing
2020    KUN     Anhui

Delete data succeed.
Query data succeed.
The number of dataline returned : 3
id      name    address
2017    Tian    Henan
2018    Wang    Shandong
2019    Li      Beijing

请按任意键继续. . .
***/