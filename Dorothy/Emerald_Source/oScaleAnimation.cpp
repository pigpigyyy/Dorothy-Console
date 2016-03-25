#include "oScaleAnimation.h"
using namespace Dorothy;

oScaleAnimation::oScaleAnimation():
m_fScaleXFrom(1.0f),
m_fScaleXTo(1.0f),
m_dScaleX(0.0f),
m_fScaleYFrom(1.0f),
m_fScaleYTo(1.0f),
m_dScaleY(0.0f){}

void oScaleAnimation::SetScale( float fScaleXFrom, float fScaleXTo,
							   float fScaleYFrom, float fScaleYTo, oUInt iDuration )
{
	m_nCount = oRoundToInt((float)iDuration*(oGame::GetInstance()->GetFPS())*0.001f);
	m_fScaleXFrom = fScaleXFrom;
	m_fScaleXTo = fScaleXTo;
	m_fScaleYFrom = fScaleYFrom;
	m_fScaleYTo = fScaleXTo;
	m_dScaleX = (float)(fScaleXTo-fScaleXFrom)/m_nCount;
	m_dScaleY = (float)(fScaleYTo-fScaleYFrom)/m_nCount;
}

void oScaleAnimation::PreStart()
{
	m_fCurrent = 0.0f;
	m_pkTarget->SetScale(m_fScaleXFrom,m_fScaleYFrom);
}

void oScaleAnimation::PreEnd()
{
	if (m_bReverse)
	{
		m_fCurrent = 0.0f;
		m_bIsReversing = false;
	    m_pkTarget->SetScale(m_fScaleXFrom,m_fScaleYFrom);
	}
	else
	{
		m_fCurrent = (float)m_nCount;
		m_pkTarget->SetScale(m_fScaleXTo,m_fScaleYTo);
	}
}

bool oScaleAnimation::UpdateFrame()
{
	if (m_bReverse)
	{
		if (m_bIsReversing)
		{
			if (m_fCurrent > 0.0f)
			{
				m_pkTarget->SetScale(m_fScaleXFrom+m_dScaleX*m_fCurrent,
					m_fScaleYFrom+m_dScaleY*m_fCurrent);
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
				m_pkTarget->SetScale(m_fScaleXFrom+m_dScaleX*m_fCurrent,
					m_fScaleYFrom+m_dScaleY*m_fCurrent);
				m_fCurrent += m_fAdd;
			}
			else
			{
				m_pkTarget->SetScale(m_fScaleXTo,m_fScaleYTo);
				m_fCurrent = (float)m_nCount;
				m_bIsReversing = true;
			}
		}
	}
	else
	{
		if (m_fCurrent < (float)m_nCount)
		{
			m_pkTarget->SetScale(m_fScaleXFrom+m_dScaleX*m_fCurrent,
				m_fScaleYFrom+m_dScaleY*m_fCurrent);
			m_fCurrent += m_fAdd;
		}
		else
		{
			return true;
		}
	}
	return false;
}