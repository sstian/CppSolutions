#pragma once

// 超级VIP会员策略类
class SuperVIPStrategy : public Strategy
{
public:
	SuperVIPStrategy();
	virtual ~SuperVIPStrategy();

	void ShowStrategy() override
	{
		std::cout << "超级VIP会员 SuperVIPStrategy::ShowStrategy()" << std::endl;
	}

};

