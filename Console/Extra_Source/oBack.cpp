#include "oBack.h"

static RECT g_kBunnyRect = {0,0,80,144};

oBack::oBack():
m_iYFrom(0),
m_iYTo(0)
{
	oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_BUNNYS);
	oSprite::SetImage(pkImage);
	oSprite::SetRenderRect(g_kBunnyRect);
	oSprite::SetPosition(0,0);
	oSprite::SetSize(160,144);
	oSprite::SetScale(2.0f,1.0f);
	oSprite::SetDetective(false);
	m_kScale.SetScale(2.0f,5.0f,2.0f,5.0f,4000);
	m_kScale.SetReverse(true);
	m_kScale.SetLoop(true);
	m_kScale.SetTarget(this);
	m_kScale.Start();
}

void oBack::SetMove( int YFrom, int YTo )
{
	m_iYFrom = YFrom;
	m_iYTo = YTo;
	m_kMove.SetMove(10,10,YFrom,YTo,5000);
	m_kMove.SetReverse(true);
	m_kMove.SetLoop(true);
	m_kMove.SetTarget(this);
	m_kMove.Start();
}