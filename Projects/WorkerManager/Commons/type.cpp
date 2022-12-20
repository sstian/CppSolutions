#include "type.h"

const char* cworker[] = {
	"工号", "姓名", "性别", "薪资", "年龄", "电话", "身份证号", "家庭住址"
};

void OutWorkerTitle()
{
	cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << "\t" << cworker[WORKER_SALARY] << "\t\t"
		<< cworker[WORKER_AGE] << "\t" << cworker[WORKER_PHONE] << "\t\t" << cworker[WORKER_IDCARD] << "\t\t" << cworker[WORKER_HOME] << endl;
}


const char* cadmin[] = {
	"用户名", "密码", "权限"
};

void OutAdminTitle()
{
	cout << cadmin[ADMIN_USERNAME] << "\t\t" << cadmin[ADMIN_PASSWORD] << "\t\t" << cadmin[ADMIN_AUTHORITY] << endl;
}
