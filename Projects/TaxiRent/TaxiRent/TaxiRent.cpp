#include "TaxiRent.h"
#include <cmath>

const double Price::TIME	= 3.0;	//等候低速计费单位时间，3，单位：min
const double Price::SPEED	= 12.0;	//等候低速速度值，12，单位：km/h
TaxiRent::TaxiRent()
{
	m_Distance		= 0.0;
	m_Time			= 0.0;
	m_TimeWaiting	= 0.0;
	m_SpeedMax		= 0.0;
	m_SpeedMin		= 0.0;
	m_Price			= 0.0;
	m_TaxiType		= Common;
}

TaxiRent::TaxiRent(TaxiType_Enum taxiType)
{
	m_Distance		= 0.0;
	m_Time			= 0.0;
	m_TimeWaiting	= 0.0;
	m_SpeedMax		= 0.0;
	m_SpeedMin		= 0.0;
	m_Price			= 0.0;
	m_TaxiType		= taxiType;
}

TaxiRent::~TaxiRent()
{
}

double TaxiRent::GetDistance()
{
	return m_Distance;
}

void TaxiRent::SetDistance(double distance)
{
	m_Distance = distance;
}

double TaxiRent::GetTime()
{
	return m_Time;
}

void TaxiRent::SetTime(double time)
{
	m_Time = time;
}

double TaxiRent::GetTimeWaiting()
{

	return m_TimeWaiting;
}

void TaxiRent::SetTimeWaiting(double timeWaiting)
{
	m_TimeWaiting = timeWaiting;
}

double TaxiRent::GetSpeedMax()
{
	//s0 = 0
	m_SpeedMax = (m_Distance - 0.0) / (m_Time - m_TimeWaiting) * 60;
	return m_SpeedMax;
}

double TaxiRent::GetSpeedMin()
{
	//s0 = 12t0
	m_SpeedMin = (m_Distance - Price::SPEED * m_TimeWaiting / 60) / (m_Time - m_TimeWaiting) * 60;
	return m_SpeedMin;
}

double TaxiRent::GetPrice()
{
	return m_Price;
}

void TaxiRent::SetPrice(double price)
{
	m_Price = price;
}


TaxiType_Enum TaxiRent::GetTaxiType()
{
	return m_TaxiType;
}

void TaxiRent::SetTaxiType(TaxiType_Enum taxiType)
{
	m_TaxiType = taxiType;
}


double TaxiRent::TotalPrice()
{
	double waitingPrice;	//等候低速计费（不含空驶费、夜间收费）
	double routinePrice;	//行驶路程费用
	double extraPrice;		//额外费用：夜间收费、合乘费用、过桥过路收费……
	double totalPrice;		//打车总费用
	struct Routine routine;					//行驶里程
	struct Price::Common commonPrice;		//普通型价位
	struct Price::Limousine LimousinePrice;	//礼宾型价位

	switch (m_TaxiType)
	{
	case Common:	//普通型
		//计算等候低速计费：v<12km/h，车公里租价/3min，不满3分钟不收费
		waitingPrice = commonPrice.RENT * ceil(m_TimeWaiting / Price::TIME);	/// double ceil(double x); 向下取整
		//计算行驶路程费用
		if (m_Distance <= routine.START)
		{
			routinePrice = commonPrice.START;	//起步费
		}
		else if (m_Distance > routine.START && m_Distance <= routine.RENT)
		{
			routinePrice = commonPrice.START + commonPrice.RENT * (m_Distance - routine.START);	//车公里租价P
		}
		else if ((m_Distance > routine.RENT) && (m_Distance <= routine.CARRY))
		{
			routinePrice = commonPrice.START + commonPrice.RENT * (routine.RENT - routine.START) + commonPrice.CARRY * (m_Distance - routine.RENT);	//空驶费1：加收 50%P/km
		}
		else
		{
			routinePrice = commonPrice.START + commonPrice.RENT * (routine.RENT - routine.START) + commonPrice.CARRY * (routine.CARRY - routine.RENT) + commonPrice.CARRY2 * (m_Distance - routine.CARRY);	//空驶费2：加收 100%P/km
		}
		//计算额外费用
		extraPrice = 0.0;
		//反解低等候低速时间
		m_TimeWaiting = (m_Price - routinePrice - extraPrice) * Price::TIME / commonPrice.RENT;
		break;
	case Limousine:	//礼宾型
		//计算等候低速计费：v<12km/h，车公里租价/3min，不满3分钟不收费
		waitingPrice = LimousinePrice.RENT * ceil(m_TimeWaiting / Price::TIME);	/// double ceil(double x); 向下取整
		//计算行驶路程费用
		if (m_Distance <= routine.START)
			routinePrice = LimousinePrice.START;	//起步费
		else if (m_Distance > routine.START && m_Distance <= routine.RENT)
			routinePrice = LimousinePrice.START + LimousinePrice.RENT * (m_Distance - routine.START);	//车公里租价P
		else if ((m_Distance > routine.RENT) & (m_Distance <= routine.CARRY))
			routinePrice = LimousinePrice.START + LimousinePrice.RENT * (routine.RENT - routine.START) + LimousinePrice.CARRY * (m_Distance - routine.RENT);	//空驶费1：加收 50%P/km
		else
			routinePrice = LimousinePrice.START + LimousinePrice.RENT * (routine.RENT - routine.START) + LimousinePrice.CARRY * (routine.CARRY - routine.RENT) + LimousinePrice.CARRY2 * (m_Distance - routine.CARRY);	//空驶费2：加收 100%P/km
		//计算额外费用
		extraPrice = 0.0;
		//反解低等候低速时间
		m_TimeWaiting = (m_Price - routinePrice - extraPrice) * Price::TIME / commonPrice.RENT;
		break;
	default:
		break;
	}

	totalPrice = waitingPrice + routinePrice + extraPrice;
	return totalPrice;
}
