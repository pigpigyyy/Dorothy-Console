#include "oCamera.h"
using namespace Dorothy;

oCamera::oCamera():
m_fZoom(1.0f),
m_fOriginX(0.0f),
m_fOriginY(0.0f),
m_pkTarget(NULL){}

oCamera::~oCamera()
{
	if (oIUpdate::IsRegistered())
	{
		oIUpdate::UnRegister();
	}
	m_pkTarget = NULL;
}

void oCamera::LockAt( const oObject* pkTarget, float fOriginX, float fOriginY )
{
	m_pkTarget = pkTarget;
	if (pkTarget != NULL)
	{
		m_fOriginX = fOriginX;
		m_fOriginY = fOriginY;
		oIUpdate::Register();
	}
	else
	{
		oIUpdate::UnRegister();
	}
}

void oCamera::Update()
{
	oCamera::Move(
		m_pkTarget->GetX()+(m_pkTarget->GetWidth()>>1),
		m_pkTarget->GetY()+(m_pkTarget->GetHeight()>>1));
}

void oCamera::Zoom( float fZoom )
{
	m_fZoom = fZoom;
	oScreen* pkScreen = oScreen::GetInstance();
	int iCenterX = pkScreen->GetViewX()+(pkScreen->GetWidth()>>1);
	int iCenterY = pkScreen->GetViewY()+(pkScreen->GetHeight()>>1);
	pkScreen->SetScale(fZoom, fZoom);
	pkScreen->SetView(iCenterX-(pkScreen->GetWidth()>>1), iCenterY-(pkScreen->GetHeight()>>1));
}

void oCamera::Move( int X, int Y )
{
	oScreen* pkScreen = oScreen::GetInstance();
	m_iX = X - (pkScreen->GetWidth()>>1);
	m_iY = Y - (pkScreen->GetHeight()>>1);
	pkScreen->SetView(m_iX, m_iY);
}

float oCamera::GetZoom() const
{
	return m_fZoom;
}

int oCamera::GetX() const
{
	return m_iX;
}

int oCamera::GetY() const
{
	return m_iY;
}

const oObject* oCamera::GetTarget() const
{
	return m_pkTarget;
}