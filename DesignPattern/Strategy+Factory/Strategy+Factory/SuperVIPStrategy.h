#pragma once

// ����VIP��Ա������
class SuperVIPStrategy : public Strategy
{
public:
	SuperVIPStrategy();
	virtual ~SuperVIPStrategy();

	void ShowStrategy() override
	{
		std::cout << "����VIP��Ա SuperVIPStrategy::ShowStrategy()" << std::endl;
	}

};

