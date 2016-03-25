#include "oBunny.h"

static RECT g_kBunnyRect[20] =
{
	{0,0,15,36},
	{0,36,15,72},
	{0,72,15,108},
	{0,108,15,144},
	{16,0,31,36},
	{16,36,31,72},
	{16,72,31,108},
	{16,108,31,144},
	{32,0,47,36},
	{32,36,47,72},
	{32,72,47,108},
	{32,108,47,144},
	{48,0,63,36},
	{48,36,63,72},
	{48,72,63,108},
	{48,108,63,144},
	{64,0,79,36},
	{64,36,79,72},
	{64,72,79,108},
	{64,108,79,144}
};

static RECT g_kRightBunnyRect[2] =
{
	{80,0,95,36},
	{80,36,95,72}
};

static RECT g_kWrongBunnyRect[2] =
{
	{80,72,95,108},
	{80,108,95,144}
};

oBunny::oBunny(int originX, int originY):
oSprite(false),
m_State(BNY_NONE),
m_iCurrentFace(0),
m_kNormalTimer(180,0),
m_kEventTimer(3000,0),
m_kRunTimer(4000),
m_iOffsetValue(1),
m_iOffsetX(0),
m_iOffsetY(-1),
m_iOriginX(originX),
m_iOriginY(originY)
{
	m_kEventTimer.OnTimer += std::make_pair(this, &oBunny::MakeBunnyAct);
	m_kNormalTimer.OnTimer += std::make_pair(this, &oBunny::MakeBunnyJump);
	m_kRunTimer.OnTimer += std::make_pair(this, &oBunny::BunnyRunAway);
	m_kRotate.OnEnd += std::make_pair(this, &oBunny::ActionEnd);
	m_kScale.OnEnd += std::make_pair(this, &oBunny::ActionEnd);
	m_kRightFrame.OnEnd += std::make_pair(this, &oBunny::ActionEnd);
	m_kWrongFrame.OnEnd += std::make_pair(this, &oBunny::ActionEnd);

	//初始化Bunny
	oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_BUNNYS);
	oSprite::SetImage(pkImage);
	oSprite::SetPosition(originX,originY);
	oSprite::SetSize(15,36);
	//正确的动画
	m_kRightFrame.SetUpFrame(2);
	for (oUInt n = 0;n < 2;n++)
	{
		m_kRightFrame.SetFrame(n,g_kRightBunnyRect[n],300);
	}
	m_kRightFrame.SetReverse(true);
	m_kRightFrame.SetTarget(this);
	//错误的动画
	m_kWrongFrame.SetUpFrame(2);
	for (oUInt n = 0;n < 2;n++)
	{
		m_kWrongFrame.SetFrame(n,g_kWrongBunnyRect[n],300);
	}
	m_kWrongFrame.SetReverse(true);
	m_kWrongFrame.SetTarget(this);
	//旋转动画
	m_kRotate.SetRotate(0,360,1000);
	m_kRotate.SetTarget(this);
	//缩放动画
	m_kScale.SetScale(1.0f,2.0,1.0f,2.0f,500);
	m_kScale.SetReverse(true);
	m_kScale.SetTarget(this);
	oBunny::Refresh();
}

void oBunny::Refresh()
{
	m_iCurrentFace = rand()%20;
	oSprite::SetRenderRect(g_kBunnyRect[m_iCurrentFace]);
	oSprite::SetPosition(m_iOriginX,m_iOriginY);
	oBunny::Reset();
	oBunny::StayHappy();
}

void oBunny::StayHappy()
{
	m_State = BNY_NORMAL;
	m_iOffsetX = 0;
	m_iOffsetY = -1;
	m_kNormalTimer.Start();
	m_kEventTimer.Start();
}

void oBunny::GoInsane()
{
	m_State = BNY_RUN;
	m_iOffsetX = (rand()%2 == 0 ? m_iOffsetValue : -m_iOffsetValue);
	m_iOffsetY = (rand()%2 == 0 ? m_iOffsetValue : -m_iOffsetValue);
	m_kRunTimer.Start();
}

void oBunny::BeGiantBunny()
{
	m_State = BNY_SCALE;
	m_kScale.Start();
}

void oBunny::Ah_Its_A_Rolling_World()
{
	m_State = BNY_ROTATE;
	m_kRotate.Start();
}

void oBunny::Update()
{
	switch (m_State)
	{
	case BNY_NONE:
		break;
	case BNY_RUN:
	case BNY_ROTATE:
	case BNY_SCALE:
	case BNY_NORMAL:
		{
			if (m_State == BNY_RUN)
			{
				oBunny::RunBunny();
			}
			oPoint kPoint = {oInput::GetInstance()->GetMouseX(),
				oInput::GetInstance()->GetMouseY()};
			vector<oObject*>& kList = m_pkGroup->GetCollisionList(kPoint, true);
			if (kList.size() > 0)
			{
				int iSize = kList.size();
				for (int i = 0;i < iSize;i++)
				{
					if (kList[i] == this)
					{
						if (oInput::GetInstance()->IsLeftMouseDown())
						{
							if (m_State == BNY_NORMAL)
							{
								if (OnActSucceeded)
								{
									OnActSucceeded(this);
								}
								oBunny::PlayWrongAnim();
							}
							else
							{
								if (OnActFailed)
								{
									OnActFailed(this);
								}
								oBunny::PlayRightAnim();
							}
						}
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void oBunny::PlayRightAnim()
{
	m_State = BNY_ANIM;
	oDataBase::GetSingleton()->GetSound(SND_CAT)->Play(false);
	oBunny::Reset();
	oSprite::SetDetective(false);
	m_kRightFrame.Start();
}

void oBunny::PlayWrongAnim()
{
	m_State = BNY_ANIM;
	oDataBase::GetSingleton()->GetSound(SND_DIE)->Play(false);
	oBunny::Reset();
	oSprite::SetDetective(false);
	m_kWrongFrame.Start();
}

void oBunny::SetOrigin( int originX,int originY )
{
	m_iOriginX = originX;
	m_iOriginY = originY;
}

void oBunny::RunBunny()
{
	int scrWidth = oScreen::GetInstance()->GetWidth();
	int scrHeight = oScreen::GetInstance()->GetHeight();
	int posX = oSprite::GetX();
	int posY = oSprite::GetY();
	if ((posX + m_iOffsetX) > (scrWidth - oSprite::GetWidth()))
	{
		posX = scrWidth - oSprite::GetWidth();
		m_iOffsetX = -m_iOffsetX;
	}
	if ((posY + m_iOffsetY) > (scrHeight - oSprite::GetHeight()))
	{
		posY = scrHeight - oSprite::GetHeight();
		m_iOffsetY = -m_iOffsetY;
	}
	if ((posX + m_iOffsetX) < 0)
	{
		posX = 0;
		m_iOffsetX = -m_iOffsetX;
	}
	if ((posY + m_iOffsetY) < 0)
	{
		posY = 0;
		m_iOffsetY = -m_iOffsetY;
	}
	//单位X碰撞检测
	oSprite::SetPosition(posX+m_iOffsetX,posY);
	vector<oObject*>& kList = m_pkGroup->GetCollisionList(this,true);
	if (kList.size() > 0)
	{
		if (kList[0]->GetX() < oSprite::GetX())
		{
			posX = kList[0]->GetX()+kList[0]->GetWidth();
		}
		else
		{
			posX = kList[0]->GetX()-oSprite::GetWidth();
		}
		m_iOffsetX = -m_iOffsetX;
	}
	else
	{
		posX += m_iOffsetX;
	}
	//单位Y碰撞检测
	oSprite::SetPosition(posX,posY+m_iOffsetY);
	kList = m_pkGroup->GetCollisionList(this,true);
	if (kList.size() > 0)
	{
		if (kList[0]->GetY() < oSprite::GetY())
		{
			posY = kList[0]->GetY()+kList[0]->GetHeight();
		}
		else
		{
			posY = kList[0]->GetY()-oSprite::GetHeight();
		}
		m_iOffsetY = -m_iOffsetY;
	}
	else
	{
		posY += m_iOffsetY;
	}
	oSprite::SetPosition(posX, posY);
}

void oBunny::SetLevel( oBunnyLevel level )
{
	m_Level = level;
	switch (level)
	{
	case LEVEL_ONE:
		m_iOffsetValue = 1;
		m_kRotate.SetSpeed(0.3f);
		m_kScale.SetSpeed(0.3f);
		m_kEventTimer.SetDelay(5000);
		break;
	case LEVEL_TWO:
		m_iOffsetValue = 2;
		m_kRotate.SetSpeed(0.7f);
		m_kScale.SetSpeed(0.7f);
		m_kEventTimer.SetDelay(3000);
		break;
	case LEVEL_THREE:
		m_iOffsetValue = 4;
		m_kRotate.SetSpeed(1.1f);
		m_kScale.SetSpeed(1.1f);
		m_kEventTimer.SetDelay(1000);
		break;
	case LEVEL_FOUR:
		m_iOffsetValue = 5;
		m_kRotate.SetSpeed(1.6f);
		m_kScale.SetSpeed(1.6f);
		m_kEventTimer.SetDelay(600);
		break;
	default:
		break;
	}
	m_kEventTimer.Start();
}

void oBunny::MakeBunnyAct()
{
	int iAction = rand()%9;
	if (iAction <= 2)
	{
		oBunny::Reset();
		if (iAction == 0)
		{
			oBunny::BeGiantBunny();
		}
		else if (iAction == 1)
		{
			oBunny::Ah_Its_A_Rolling_World();
		}
		else
		{
			oBunny::GoInsane();
		}
	}
}

void oBunny::MakeBunnyJump()
{
	oSprite::SetPosition(oSprite::GetX(), oSprite::GetY()+m_iOffsetY);
	m_iOffsetY = -m_iOffsetY;
}

void oBunny::BunnyRunAway()
{
	oSprite::SetPosition(m_iOriginX,m_iOriginY);
	if (OnActSucceeded)
	{
		OnActSucceeded(this);
	}
	oBunny::PlayWrongAnim();
}

void oBunny::ActionEnd( oAnimation* pkTarget )
{
	if (&m_kRotate == pkTarget || &m_kScale == pkTarget)
	{
		if (OnActSucceeded)
		{
			OnActSucceeded(this);
		}
		oBunny::PlayWrongAnim();
	}
	else
	{
		oBunny::Reset();
		oSprite::SetDetective(true);
		oBunny::StayHappy();
	}
}

void oBunny::Stop()
{
	m_State = BNY_NONE;
	m_kEventTimer.Stop();
	if (m_kNormalTimer.IsRunning())
	{
		m_kNormalTimer.Stop();
	}
	if (m_kRunTimer.IsRunning())
	{
		m_kRunTimer.Stop();
	}
	if (m_kRotate.IsPlaying())
	{
		m_kRotate.Stop();
	}
	if (m_kScale.IsPlaying())
	{
		m_kScale.Stop();
	}
	if (m_kRightFrame.IsPlaying())
	{
		m_kRightFrame.Stop();
	}
	if (m_kWrongFrame.IsPlaying())
	{
		m_kWrongFrame.Stop();
	}
}

void oBunny::Reset()
{
	oBunny::Stop();
	oSprite::SetDetective(true);
	oSprite::SetRenderRect(g_kBunnyRect[m_iCurrentFace]);
	oSprite::SetAngle(0);
	oSprite::SetScale(1.0f, 1.0f);
	oSprite::SetPosition(m_iOriginX, m_iOriginY);
}
