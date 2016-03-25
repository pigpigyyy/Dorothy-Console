#include "oDotPaint.h"
using namespace Dorothy;

oDotPaint::oDotPaint():
m_pkPointList(NULL),
m_iNumber(0),
m_Color(COLOR_NONE),
m_Ch(' '){}

void oDotPaint::Set( const oPoint* pointList, oUInt number, oColor color, char ch )
{
	m_pkPointList = pointList;
	m_iNumber = number;
	m_Color = color;
	m_Ch = ch;
}

void oDotPaint::SetPoint( const oPoint* pointList, oUInt number )
{
	m_pkPointList = pointList;
	m_iNumber = number;
}

void oDotPaint::SetColor( oColor color )
{
	m_Color = color;
}

void oDotPaint::SetChar( char ch )
{
	m_Ch = ch;
}

void oDotPaint::Render()
{
	if (oIRender::IsVisible())
	{
		oScreen::GetInstance()->DrawPoint(m_pkPointList,m_iNumber,m_Color,m_Ch);
	}
}