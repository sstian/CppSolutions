#pragma once

#include <iostream>

// ���Գ�����
class Strategy
{
public:
	Strategy();
	virtual ~Strategy();

	void virtual ShowStrategy() = 0;
};

