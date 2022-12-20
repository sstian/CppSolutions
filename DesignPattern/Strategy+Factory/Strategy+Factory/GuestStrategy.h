#pragma once

// 普通用户策略类
class GuestStrategy : public Strategy
{
public:
	GuestStrategy();
	virtual ~GuestStrategy();

	void ShowStrategy() override
	{
		std::cout << "普通用户 GuestStrategy::ShowStrategy()" << std::endl;
	}

};

