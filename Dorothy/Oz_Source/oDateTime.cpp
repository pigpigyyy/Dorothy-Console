#include "oDateTime.h"
using namespace Dorothy;

oDateTime::oDateTime()
{
	oDateTime::Update();
}

void oDateTime::Update()
{
	time_t iTempTimeDate;
	/*得到当前时间和日期*/
	::time(&iTempTimeDate);
	::localtime_s(&m_kTime,&iTempTimeDate);
}

oUInt32 oDateTime::GetSeconds() const
{
	return m_kTime.tm_sec;
}

oUInt32 oDateTime::GetMinutes() const
{
	return m_kTime.tm_min;
}

oUInt32 oDateTime::GetHours() const
{
	return m_kTime.tm_hour;
}

oUInt32 oDateTime::GetDay() const
{
	return m_kTime.tm_mday;
}

oUInt32 oDateTime::GetMonth() const
{
	return m_kTime.tm_mon + 1;
}

oUInt32 oDateTime::GetYear() const
{
	return m_kTime.tm_year + 1900;
}