#pragma once

// ��ͨ�û�������
class GuestStrategy : public Strategy
{
public:
	GuestStrategy();
	virtual ~GuestStrategy();

	void ShowStrategy() override
	{
		std::cout << "��ͨ�û� GuestStrategy::ShowStrategy()" << std::endl;
	}

};

