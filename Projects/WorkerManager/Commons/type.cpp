#include "type.h"

const char* cworker[] = {
	"����", "����", "�Ա�", "н��", "����", "�绰", "���֤��", "��ͥסַ"
};

void OutWorkerTitle()
{
	cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << "\t" << cworker[WORKER_SALARY] << "\t\t"
		<< cworker[WORKER_AGE] << "\t" << cworker[WORKER_PHONE] << "\t\t" << cworker[WORKER_IDCARD] << "\t\t" << cworker[WORKER_HOME] << endl;
}


const char* cadmin[] = {
	"�û���", "����", "Ȩ��"
};

void OutAdminTitle()
{
	cout << cadmin[ADMIN_USERNAME] << "\t\t" << cadmin[ADMIN_PASSWORD] << "\t\t" << cadmin[ADMIN_AUTHORITY] << endl;
}
