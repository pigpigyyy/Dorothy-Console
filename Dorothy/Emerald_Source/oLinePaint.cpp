#include "oLinePaint.h"
using namespace Dorothy;

oLinePaint::oLinePaint():
m_Color(COLOR_NONE),
m_Ch(' ')
{
	ZeroMemory(&m_kStart,sizeof(oPoint));
	ZeroMemory(&m_kEnd,sizeof(oPoint));
}

void oLinePaint::Set( const oPoint& start,const oPoint& end, oColor color, char ch )
{
	m_kStart = start;
	m_kEnd = end;
	m_Color = color;
	m_Ch = ch;
}

void oLinePaint::SetLine( const oPoint& start,const oPoint& end )
{
	m_kStart = start;
	m_kEnd = end;
}

void oLinePaint::SetColor( oColor color )
{
	m_Color = color;
}

void oLinePaint::SetChar( char ch )
{
	m_Ch = ch;
}

void oLinePaint::Render()
{
	if (oIRender::IsVisible())
	{
		oScreen::GetInstance()->DrawLine(m_kStart,m_kEnd,m_Color,m_Ch);
	}
}