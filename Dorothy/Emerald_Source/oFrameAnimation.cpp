#include "oFrameAnimation.h"
using namespace Dorothy;

oFrameAnimation::oFrameAnimation():
m_pkRenderRectList(NULL),
m_pnKeepTime(NULL),
m_iCurrentFrame(0),
m_nFrameNum(0){}

oFrameAnimation::~oFrameAnimation()
{
	if (m_pkRenderRectList != NULL)
	{
		delete [] m_pkRenderRectList;
		m_pkRenderRectList = NULL;
	}
	if (m_pnKeepTime != NULL)
	{
		delete [] m_pnKeepTime;
		m_pnKeepTime = NULL;
	}
}

void oFrameAnimation::SetUpFrame( oUInt nFrame )
{
	if (m_pkRenderRectList != NULL)
	{
		delete [] m_pkRenderRectList;
	}
	if (m_pnKeepTime != NULL)
	{
		delete [] m_pnKeepTime;
	}
	m_pkRenderRectList = new RECT[nFrame]();
	m_pnKeepTime = new oUInt[nFrame]();
	m_nFrameNum = nFrame;
}

void oFrameAnimation::SetFrame( oUInt nSubScript,const RECT& kRenderRect,oUInt nKeepTime )
{
	m_pkRenderRectList[nSubScript].left = kRenderRect.left;
	m_pkRenderRectList[nSubScript].top = kRenderRect.top;
	m_pkRenderRectList[nSubScript].right = kRenderRect.right;
	m_pkRenderRectList[nSubScript].bottom = kRenderRect.bottom;
	m_pnKeepTime[nSubScript] = oRoundToInt((float)nKeepTime*(oGame::GetInstance()->GetFPS())*0.001f);
}

void oFrameAnimation::PreStart()
{
	m_fCurrent = 0.0f;
	m_iCurrentFrame = 0;
	m_nCount = m_pnKeepTime[0];
	m_pkTarget->SetRenderRect(m_pkRenderRectList[0]);
}

void oFrameAnimation::PreEnd()
{
	if (m_bReverse)
	{
		m_iCurrentFrame = 0;
		m_fCurrent = 0.0f;
		m_pkTarget->SetRenderRect(m_pkRenderRectList[0]);
	}
	else
	{
		m_iCurrentFrame = m_nFrameNum-1;
		m_fCurrent = (float)m_pnKeepTime[m_iCurrentFrame];
		m_pkTarget->SetRenderRect(m_pkRenderRectList[m_iCurrentFrame]);
	}
}

bool oFrameAnimation::UpdateFrame()
{
	if (m_bReverse)
	{
		if (m_bIsReversing)
		{
			if (m_fCurrent >= 0.0f)
			{
				m_fCurrent -= m_fAdd;
			}
			else
			{
				m_iCurrentFrame--;
				if (m_iCurrentFrame < 0)
				{
					m_bIsReversing = false;
					return true;
				}
				else
				{
					m_fCurrent = (float)m_pnKeepTime[m_iCurrentFrame];
					m_pkTarget->SetRenderRect(m_pkRenderRectList[m_iCurrentFrame]);
				}
			}
		}
		else
		{
			if (m_fCurrent < (float)m_nCount)
			{
				m_fCurrent += m_fAdd;
			}
			else
			{
				m_iCurrentFrame++;
				if (m_iCurrentFrame >= (int)m_nFrameNum)
				{
					m_iCurrentFrame--;
					m_fCurrent = (float)m_pnKeepTime[m_iCurrentFrame];
					m_bIsReversing = true;
				}
				else
				{
					m_fCurrent = 0.0f;
					m_nCount = m_pnKeepTime[m_iCurrentFrame];
					m_pkTarget->SetRenderRect(m_pkRenderRectList[m_iCurrentFrame]);
				}
			}
		}
	}
	else
	{
		if (m_fCurrent < (float)m_nCount)
		{
			m_fCurrent += m_fAdd;
		}
		else
		{
			m_iCurrentFrame++;
			if (m_iCurrentFrame >= (int)m_nFrameNum)
			{
				return true;
			}
			else
			{
				m_fCurrent = 0.0f;
				m_nCount = m_pnKeepTime[m_iCurrentFrame];
				m_pkTarget->SetRenderRect(m_pkRenderRectList[m_iCurrentFrame]);
			}
		}
	}
	return false;
}

void oFrameAnimation::operator=( const oFrameAnimation& kFrame )
{
	if (&kFrame == this)
	{
		return;
	}
	memcpy((oAnimation*)this,(oAnimation*)&kFrame,sizeof(oAnimation));
	oFrameAnimation::SetUpFrame(kFrame.m_nFrameNum);
	for (oUInt n = 0;n < kFrame.m_nFrameNum;n++)
	{
		oFrameAnimation::SetFrame(n,kFrame.m_pkRenderRectList[n],kFrame.m_pnKeepTime[n]);
	}
}