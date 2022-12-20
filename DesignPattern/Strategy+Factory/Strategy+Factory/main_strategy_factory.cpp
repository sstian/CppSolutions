/*
	2020.03.10 20:22 Tuesday 
	����ģʽ+���󹤳�ģʽ �������if-else
*/

#include <iostream>
#include "Strategy.h"
#include "MemberFactory.h"

using namespace std;


int main()
{
	cout << "*** Strategy + Factory ***" << endl;

	MemberFactory* memfac = new MemberFactory();
	memfac->GetStragegy(MemberFactory::StrategyType::GUEST)->ShowStrategy();
	memfac->GetStragegy(MemberFactory::StrategyType::VIP)->ShowStrategy();
	memfac->GetStragegy(MemberFactory::StrategyType::SVIP)->ShowStrategy();
	delete memfac;

	system("pause");
	return 0;
}

/*** ��VS2017���н����
*** Strategy + Factory ***
��ͨ�û� GuestStrategy::ShowStrategy()
VIP��Ա VipStrategy::ShowStrategy()
����VIP��Ա SuperVIPStrategy::ShowStrategy()
�밴���������. . .

***/