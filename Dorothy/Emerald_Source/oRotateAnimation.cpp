#include "oRotateAnimation.h"
using namespace Dorothy;

oRotateAnimation::oRotateAnimation():
m_iAngleFrom(0),
m_iAngleTo(0),
m_dAngle(0.0f){}

void oRotateAnimation::SetRotate( int iAngleFrom,int iAngleTo,oUInt iDuration )
{
	m_nCount = oRoundToInt((float)iDuration*(oGame::GetInstance()->GetFPS())*0.001f);
	m_iAngleFrom = iAngleFrom;
	m_iAngleTo = iAngleTo;
	m_dAngle = (float)(iAngleTo-iAngleFrom)/m_nCount;
}

void oRotateAnimation::PreStart()
{
	m_fCurrent = 0.0f;
	m_pkTarget->SetAngle(m_iAngleFrom);
}

void oRotateAnimation::PreEnd()
{
	if (m_bReverse)
	{
		m_fCurrent = 0.0f;
		m_bIsReversing = false;
		m_pkTarget->SetAngle(m_iAngleFrom);
	}
	else
	{
		m_fCurrent = (float)m_nCount;
		m_pkTarget->SetAngle(m_iAngleTo);
	}
}

bool oRotateAnimation::UpdateFrame()
{
	if (m_bReverse)
	{
		if (m_bIsReversing)
		{
			if (m_fCurrent >= 0.0f)
			{
				m_pkTarget->SetAngle(m_iAngleFrom+oRoundToInt(m_dAngle*m_fCurrent));
				m_fCurrent -= m_fAdd;
			}
			else
			{
				m_bIsReversing = false;
				return true;
			}
		}
		else
		{
			if (m_fCurrent < (float)m_nCount)
			{
				m_pkTarget->SetAngle(m_iAngleFrom+oRoundToInt(m_dAngle*m_fCurrent));
				m_fCurrent += m_fAdd;
			}
			else
			{
				m_pkTarget->SetAngle(m_iAngleTo);
				m_fCurrent = (float)m_nCount;
				m_bIsReversing = true;
			}
		}
	}
	else
	{
		if (m_fCurrent < (float)m_nCount)
		{
			m_pkTarget->SetAngle(m_iAngleFrom+oRoundToInt(m_dAngle*m_fCurrent));
			m_fCurrent += m_fAdd;
		}
		else
		{
			return true;
		}
	}
	return false;
}