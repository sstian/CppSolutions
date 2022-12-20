

#include "Strategy.h"
#include "GuestStrategy.h"
#include "VIPStrategy.h"
#include "SuperVIPStrategy.h"
#include "MemberFactory.h"


const std::string MemberFactory::StrategyType::GUEST = "guest";
const std::string MemberFactory::StrategyType::VIP = "vip";
const std::string MemberFactory::StrategyType::SVIP = "svip";


MemberFactory::MemberFactory()
{
	this->m_mapss.clear();
	this->Register();
}


MemberFactory::~MemberFactory()
{
	this->m_mapss.clear();
}

void MemberFactory::Register()
{
	m_mapss.insert(std::make_pair(StrategyType::GUEST, new GuestStrategy()));
	m_mapss.insert(std::make_pair(StrategyType::VIP, new VIPStrategy()));
	m_mapss.insert(std::make_pair(StrategyType::SVIP, new SuperVIPStrategy()));
}
