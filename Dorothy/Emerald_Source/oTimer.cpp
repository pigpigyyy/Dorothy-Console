#include "oTimer.h"
#include "oGame.h"
using namespace Dorothy;

oTimer::oTimer( oUInt nDelay,oUInt nLoop ):
m_bRun(false),
m_nLoop(nLoop)
{
	oTimer::SetDelay(nDelay);
}

void oTimer::SetDelay( oUInt nDelay )
{
	m_nCount = oRoundToInt(((float)nDelay*(oGame::GetInstance()->GetFPS()))*0.001f);
}

void oTimer::SetLoop( oUInt nLoop )
{
	m_nLoop = nLoop;
}

void oTimer::Start()
{
	m_nCurrentLoop = 0;
	m_nCurrentCount = 0;
	oIUpdate::Register();
	m_bRun = true;
}

void oTimer::Update()
{
	if (m_bRun)
	{
		if (++m_nCurrentCount > m_nCount)
		{
			if (++m_nCurrentLoop < m_nLoop || m_nLoop == 0)
			{
				m_nCurrentCount = 0;
			}
			else
			{
				oIUpdate::UnRegister();
				m_bRun = false;
			}
			if (OnTimer)
			{
				OnTimer();
			}
		}
	}
}

void oTimer::Stop()
{
	oIUpdate::UnRegister();
	m_bRun = false;
}

bool oTimer::IsRunning() const
{
	return m_bRun;
}

oUInt oTimer::GetCurrentLoop() const
{
	return m_nCurrentLoop;
}

oUInt oTimer::GetLoop() const
{
	return m_nLoop;
}