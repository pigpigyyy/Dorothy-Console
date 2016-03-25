#include "oMoveAnimation.h"
using namespace Dorothy;

oMoveAnimation::oMoveAnimation():
m_iMoveXFrom(0),
m_iMoveXTo(0),
m_dMoveX(0.0f),
m_iMoveYFrom(0),
m_iMoveYTo(0),
m_dMoveY(0.0f){}

void oMoveAnimation::SetMove( int iMoveXFrom, int iMoveXTo,
							   int iMoveYFrom, int iMoveYTo, oUInt iDuration )
{
	m_nCount = oRoundToInt((float)iDuration*(oGame::GetInstance()->GetFPS())*0.001f);
	m_iMoveXFrom = iMoveXFrom;
	m_iMoveXTo = iMoveXTo;
	m_iMoveYFrom = iMoveYFrom;
	m_iMoveYTo = iMoveYTo;
	m_dMoveX = (float)(iMoveXTo-iMoveXFrom)/m_nCount;
	m_dMoveY = (float)(iMoveYTo-iMoveYFrom)/m_nCount;
}

void oMoveAnimation::PreStart()
{
	m_fCurrent = 0.0f;
	m_pkTarget->SetPosition(m_iMoveXFrom,m_iMoveYFrom);
}

void oMoveAnimation::PreEnd()
{
	if (m_bReverse)
	{
		m_fCurrent = 0.0f;
		m_bIsReversing = false;
		m_pkTarget->SetPosition(m_iMoveXFrom,m_iMoveYFrom);
	}
	else
	{
		m_fCurrent = (float)m_nCount;
		m_pkTarget->SetPosition(m_iMoveXTo,m_iMoveYTo);
	}
}

bool oMoveAnimation::UpdateFrame()
{
	if (m_bReverse)
	{
		if (m_bIsReversing)
		{
			if (m_fCurrent > 0.0f)
			{
				m_pkTarget->SetPosition(m_iMoveXFrom+oRoundToInt(m_dMoveX*m_fCurrent),
					m_iMoveYFrom+oRoundToInt(m_dMoveY*m_fCurrent));
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
				m_pkTarget->SetPosition(m_iMoveXFrom+oRoundToInt(m_dMoveX*m_fCurrent),
					m_iMoveYFrom+oRoundToInt(m_dMoveY*m_fCurrent));
				m_fCurrent += m_fAdd;
			}
			else
			{
				m_pkTarget->SetPosition(m_iMoveXTo,m_iMoveYTo);
				m_fCurrent = (float)m_nCount-m_fAdd;
				m_bIsReversing = true;
			}
		}
	}
	else
	{
		if (m_fCurrent < (float)m_nCount)
		{
			m_pkTarget->SetPosition(m_iMoveXFrom+oRoundToInt(m_dMoveX*m_fCurrent),
				m_iMoveYFrom+oRoundToInt(m_dMoveY*m_fCurrent));
			m_fCurrent += m_fAdd;
		}
		else
		{
			return true;
		}
	}
	return false;
}