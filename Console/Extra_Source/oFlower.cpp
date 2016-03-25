#include "oFlower.h"

static RECT g_kFlowerRect[8] =
{
	{0,0,3,3},
	{0,3,4,7},
	{0,7,5,12},
	{0,12,6,18},
	{0,18,9,27},
	{0,27,23,49},
	{0,49,27,76},
	{0,76,33,106}
};

oFlower::oFlower()
{
	oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_FLOWER);
	oSprite::SetImage(pkImage);
	oSprite::SetRenderRect(g_kFlowerRect[0]);
	oSprite::SetSize(4, 4);
	m_kFrame.SetUpFrame(8);
	for (oUInt o = 0; o < 8; o++)
	{
		m_kFrame.SetFrame(o, g_kFlowerRect[o], o * 60);
	}
	m_kFrame.SetLoop(true);
	m_kFrame.SetReverse(true);
	m_kFrame.SetTarget(this);
	m_kFrame.Start();
	m_kVector.X = (rand() % 2 == 0 ? 1 : -1);
	m_kVector.Y = (rand() % 2 == 0 ? 1 : -1);
	oIUpdate::Register();
}

void oFlower::Update()
{
	int scrWidth = oScreen::GetInstance()->GetWidth();
	int scrHeight = oScreen::GetInstance()->GetHeight();
	int posX = oSprite::GetX();
	int posY = oSprite::GetY();
	if ((posX + m_kVector.X) > (scrWidth - oSprite::GetWidth()))
	{
		posX = scrWidth - oSprite::GetWidth();
		m_kVector.X = -m_kVector.X;
	}
	if ((posY + m_kVector.Y) > (scrHeight - oSprite::GetHeight()))
	{
		posY = scrHeight - oSprite::GetHeight();
		m_kVector.Y = -m_kVector.Y;
	}
	if ((posX + m_kVector.X) < 0)
	{
		posX = 0;
		m_kVector.X = -m_kVector.X;
	}
	if ((posY + m_kVector.Y) < 0)
	{
		posY = 0;
		m_kVector.Y = -m_kVector.Y;
	}
	//µ¥Î»XÅö×²¼ì²â
	oSprite::SetPosition(posX + m_kVector.X, posY);
	vector<oObject*>& kList = m_pkGroup->GetCollisionList(this, false);
	if (kList.size() > 0)
	{
		if (kList[0]->GetX() < oSprite::GetX())
		{
			posX = kList[0]->GetX() + kList[0]->GetWidth();
		}
		else
		{
			posX = kList[0]->GetX() - oSprite::GetWidth();
		}
		m_kVector.X = -m_kVector.X;
	}
	else
	{
		posX += m_kVector.X;
	}
	//µ¥Î»YÅö×²¼ì²â
	oSprite::SetPosition(posX, posY + m_kVector.Y);
	kList = m_pkGroup->GetCollisionList(this, false);
	if (kList.size() > 0)
	{
		if (kList[0]->GetY() < oSprite::GetY())
		{
			posY = kList[0]->GetY() + kList[0]->GetHeight();
		}
		else
		{
			posY = kList[0]->GetY() - oSprite::GetHeight();
		}
		m_kVector.Y = -m_kVector.Y;
	}
	else
	{
		posY += m_kVector.Y;
	}
	oSprite::SetPosition(posX, posY);
}
