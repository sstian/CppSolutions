#pragma once

#include <map>
#include <string>

// 会员抽象工厂类
class MemberFactory
{
public:
	// 类型定义
	using mapss = std::map<std::string, Strategy*>;

	// 一堆常量字符串声明，类外定义
	// 变量名与字符串值一致，区别在于大小写
	struct StrategyType
	{
		static const std::string GUEST;
		static const std::string VIP;
		static const std::string SVIP;
	};

public:
	MemberFactory();
	virtual ~MemberFactory();

	Strategy* GetStragegy(std::string strategyType)
	{
		if (strategyType.empty())
			return nullptr;

		return m_mapss.at(strategyType);
	}

private:
	// 注册策略
	void Register();

private:
	mapss m_mapss;
};

