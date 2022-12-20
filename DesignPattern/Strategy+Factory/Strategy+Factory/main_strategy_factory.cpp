/*
	2020.03.10 20:22 Tuesday 
	策略模式+抽象工厂模式 解决多重if-else
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

/*** 在VS2017运行结果：
*** Strategy + Factory ***
普通用户 GuestStrategy::ShowStrategy()
VIP会员 VipStrategy::ShowStrategy()
超级VIP会员 SuperVIPStrategy::ShowStrategy()
请按任意键继续. . .

***/