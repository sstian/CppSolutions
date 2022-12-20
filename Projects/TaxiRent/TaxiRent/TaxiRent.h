#pragma once

enum TaxiType_Enum { Common = 1, /*普通型*/ Limousine = 2 /*礼宾型（含未更新豪华型）*/};	//巡游出租车类型

struct Routine	//运行里程，单位：km
{
	const double START	= 3.0;	//起步里程 3.0
	const double RENT	= 10.0;	//车公里租价里程 10.0
	const double CARRY	= 35.0;	//空驶里程 35.0
};
struct Price	//里程价位，单位：元
{
	static const double TIME;	//等候低速计费单位时间，3，单位：min
	static const double SPEED;	//等候低速速度值，12，单位：km/h
	struct Common	//普通型
	{
		const double START	= 10.0;			//起步价 10.0
		const double RENT	= 2.0;			//车公里租价P 2.0
		const double CARRY	= 1.5 * RENT;	//空驶费：加收 50%*P，3.0
		const double CARRY2 = 2.0 * RENT;	//空驶费：加收 100%P，4.0
	};
	struct Limousine	//礼宾型
	{
		const double START	= 12.0;			//起步价 12.0
		const double RENT	= 2.5;			//车公里租价P 2.5
		const double CARRY	= 1.5 * RENT;	//空驶费：加收 50%*P，3.75
		const double CARRY2 = 2.0 * RENT;	//空驶费：加收 100%P，5.0
	};
};


class TaxiRent	//出租车运价
{
public:
	//默认出租车类型：普通型
	TaxiRent();
	TaxiRent(TaxiType_Enum taxiType);
	virtual~TaxiRent();

	double	GetDistance();
	//设置总里程，单位：km
	void	SetDistance(double distance);

	double	GetTime();
	//设置总时间，单位：min
	void	SetTime(double time);

	double	GetTimeWaiting();
	//设置低速等候时间，单位：min
	void	SetTimeWaiting(double timeWaiting);

	//平均速度V_=(S-s0)/(T-t0). 0<=v<12km/h,则0<=s0<12t0: s0=0,v_max; s0=12to,v_min.
	//获取最大平均速度
	double	GetSpeedMax();
	//获取最小平均速度
	double	GetSpeedMin();

	double	GetPrice();
	//设置打车总费用，单位：元
	void	SetPrice(double price);

	TaxiType_Enum	GetTaxiType();
	void			SetTaxiType(TaxiType_Enum taxiType);

	//计算行程总费用，单位：元
	double TotalPrice();
private:
	double m_Distance;	//行驶里程S，单位：km
	double m_Time;		//行驶时间T，单位：min
	double m_TimeWaiting;	//等候低速时间t0（v<12km/h），单位：min（默认为0）
	double m_SpeedMax;		//平均速度最大值，v0=0，单位：km/h
	double m_SpeedMin;		//平均速度最小值，v0=12km/h，单位：km/h
	double m_Price;			//打车总价，单位：元
	TaxiType_Enum m_TaxiType;	// 出租车类型
};