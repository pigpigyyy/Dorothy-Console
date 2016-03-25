#include "oAnimation.h"
using namespace Dorothy;

oAnimation::oAnimation():
m_bPlay(false),
m_bLoop(false),
m_bReverse(false),
m_bIsReversing(false),
m_nCount(0),
m_fAdd(1.0f),
m_fCurrent(0.0f){}

void oAnimation::SetTarget( oSprite* pkUnit )
{
	m_pkTarget = pkUnit;
}

void oAnimation::SetSpeed( float fSpeed )
{
	if (fSpeed >= 0)
	{
		m_fAdd = 1.0f*fSpeed;
	}
}

void oAnimation::SetLoop( bool bLoop )
{
	m_bLoop = bLoop;
}

void oAnimation::SetReverse( bool bReverse )
{
	m_bReverse = bReverse;
}

void oAnimation::Update()
{
	if (m_bPlay)
	{
		if (this->UpdateFrame())
		{
			if (OnEnd)
			{
				OnEnd(this);
			}
			if (m_bLoop)
			{
				this->PreStart();
				this->UpdateFrame();
			}
			else
			{
				m_bPlay = false;
				this->PreEnd();
				oIUpdate::UnRegister();
			}
		}
	}
}

oSprite* oAnimation::GetTarget()
{
	return m_pkTarget;
}

void oAnimation::Start()
{
	m_bPlay = true;
	this->PreStart();
	oIUpdate::Register();
}

void oAnimation::End()
{
	m_bPlay = false;
	this->PreEnd();
	oIUpdate::UnRegister();
}

void oAnimation::Stop()
{
	m_bPlay = false;
	oIUpdate::UnRegister();
}

bool oAnimation::IsPlaying() const
{
	return m_bPlay;
}