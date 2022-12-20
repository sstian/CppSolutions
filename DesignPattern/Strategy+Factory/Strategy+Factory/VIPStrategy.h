#pragma once

// VIP会员策略类
class VIPStrategy : public Strategy
{
public:
	VIPStrategy();
	virtual ~VIPStrategy();

	void ShowStrategy() override
	{
		std::cout << "VIP会员 VipStrategy::ShowStrategy()" << std::endl;
	}

};

