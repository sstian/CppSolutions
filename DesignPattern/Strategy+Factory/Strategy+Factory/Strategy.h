#pragma once

#include <iostream>

// ²ßÂÔ³éÏóÀà
class Strategy
{
public:
	Strategy();
	virtual ~Strategy();

	void virtual ShowStrategy() = 0;
};

