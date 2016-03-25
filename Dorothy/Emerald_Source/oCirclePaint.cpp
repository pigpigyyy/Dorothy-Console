#include "oCirclePaint.h"
using namespace Dorothy;

oCirclePaint::oCirclePaint():
m_iRadius(0),
m_Color(COLOR_NONE),
m_Ch(' ')
{
	ZeroMemory(&m_kCenter,sizeof(oPoint));
}

void oCirclePaint::Set( const oPoint& kCenter, int iRadius, oColor color, char ch )
{
	m_kCenter = kCenter;
	m_iRadius = iRadius;
	m_Color = color;
	m_Ch = ch;
}

void oCirclePaint::SetCenter( const oPoint& kCenter )
{
	m_kCenter = kCenter;
}

void oCirclePaint::SetRadius( int iRadius )
{
	m_iRadius = iRadius;
}

void oCirclePaint::SetColor( oColor color )
{
	m_Color = color;
}

void oCirclePaint::SetChar( char ch )
{
	m_Ch = ch;
}

void oCirclePaint::Render()
{
	if (oIRender::IsVisible())
	{
		oScreen::GetInstance()->DrawCircle(m_kCenter,m_iRadius,m_Color,m_Ch);
	}
}