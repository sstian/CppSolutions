#pragma once

#include <map>
#include <string>

// ��Ա���󹤳���
class MemberFactory
{
public:
	// ���Ͷ���
	using mapss = std::map<std::string, Strategy*>;

	// һ�ѳ����ַ������������ⶨ��
	// ���������ַ���ֵһ�£��������ڴ�Сд
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
	// ע�����
	void Register();

private:
	mapss m_mapss;
};

