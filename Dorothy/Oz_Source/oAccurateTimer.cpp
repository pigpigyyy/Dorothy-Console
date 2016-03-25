#include "oAccurateTimer.h"
using namespace Dorothy;

oAccurateTimer::oAccurateTimer():
m_bRun(false)
{
	m_iCount.QuadPart = 0;
	/*得到硬件频率*/
	QueryPerformanceFrequency(&m_iFrequency);
}

void oAccurateTimer::ZeroCount()
{
	m_iCount.QuadPart = 0;
}

void oAccurateTimer::Start()
{
	m_bRun = true;
	m_iCount.QuadPart = 0;
	QueryPerformanceCounter(&m_iCurrentQuery);
}

float oAccurateTimer::GetCount()
{
	if (m_bRun)
	{
		m_iLastQuery.QuadPart = m_iCurrentQuery.QuadPart;
		QueryPerformanceCounter(&m_iCurrentQuery);
		m_iCount.QuadPart += (m_iCurrentQuery.QuadPart - m_iLastQuery.QuadPart);
		/*转化为浮点型，以秒为单位计算delta时间*/
		return (float)(m_iCount.QuadPart)/(float)(m_iFrequency.QuadPart);
	}
	return 0.0f;
}

void oAccurateTimer::Stop()
{
	m_bRun = false;
}

bool oAccurateTimer::IsRunning()
{
	return m_bRun;
}