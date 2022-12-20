/*
	Excel字段测试类
*/

#pragma once

#include "stdafx.h"

class Puck
{
public:
	Puck(){ }
	Puck(CString& puckNumber, CTime& arriveDateTime, CString& arriveFlight, CString& arriveType, CString& planeType, 
		 CTime& leaveDateTime, CString& leaveFlight, CString& leaveType, CString& onlineAirport, CString& downlineAirport)
		:m_puckNumber(puckNumber),
		m_arriveDateTime(arriveDateTime),
		m_arriveFlight(arriveFlight),
		m_arriveType(arriveType),
		m_planeType(planeType),
		m_leaveDateTime(leaveDateTime),
		m_leaveFlight(leaveFlight),
		m_leaveType(leaveType),
		m_onlineAirport(onlineAirport),
		m_downlineAirport(downlineAirport)
	{ }
		virtual~Puck(){ }

		void setPuckNumber(const CString& puckNumber) { m_puckNumber = puckNumber; }
		void setArriveDateTime(const CTime& arriveDateTime) { m_arriveDateTime = arriveDateTime; }
		void setArriveFlight(const CString& arriveFlight) { m_arriveFlight = arriveFlight; }
		void setArriveType(const CString& arriveType) { m_arriveType = arriveType; }
		void setPlaneType(const CString& planeType) { m_planeType = planeType; }
		void setLeaveDateTime(const CTime& leaveDateTime) { m_leaveDateTime = leaveDateTime; }
		void setLeaveFlight(const CString& leaveFlight) { m_leaveFlight = leaveFlight; }
		void setLeaveType(const CString& leaveType) { m_leaveType = leaveType; }
		void setOnlineAriport(const CString& onlineAirport) { m_onlineAirport = onlineAirport; }
		void setDownlineAriport(const CString& downlineAirport) { m_downlineAirport = downlineAirport; }
private:
	CString m_puckNumber;		//飞机转场记录号
	CTime	m_arriveDateTime;	//到达日期时刻
	CString m_arriveFlight;		//到达航班
	CString m_arriveType;		//到达类型
	CString m_planeType;		//飞机型号
	CTime	m_leaveDateTime;	//出发日期时刻
	CString m_leaveFlight;		//出发航班
	CString m_leaveType;		//出发类型
	CString m_onlineAirport;	//上线机场
	CString m_downlineAirport;	//下线机场
};