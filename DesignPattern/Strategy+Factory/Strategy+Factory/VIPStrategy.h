#pragma once

// VIP��Ա������
class VIPStrategy : public Strategy
{
public:
	VIPStrategy();
	virtual ~VIPStrategy();

	void ShowStrategy() override
	{
		std::cout << "VIP��Ա VipStrategy::ShowStrategy()" << std::endl;
	}

};

