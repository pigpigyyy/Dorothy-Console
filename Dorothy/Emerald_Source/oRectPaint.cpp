#include "oRectPaint.h"
using namespace Dorothy;

oRectPaint::oRectPaint():
m_Color(COLOR_NONE),
m_Ch(' ')
{
	ZeroMemory(&m_kRect,sizeof(RECT));
}

void oRectPaint::Set( const RECT& rect, oColor color, char ch )
{
	m_kRect = rect;
	m_Color = color;
	m_Ch = ch;
}

void oRectPaint::SetColor( oColor color )
{
	m_Color = color;
}

void oRectPaint::SetRect( const RECT& rect )
{
	m_kRect = rect;
}

void oRectPaint::SetChar( char ch )
{
	m_Ch = ch;
}

void oRectPaint::Render()
{
	if (oIRender::IsVisible())
	{
		oScreen::GetInstance()->DrawRectangle(m_kRect,m_Color,m_Ch);
	}
}