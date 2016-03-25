#include "oScreen.h"
using namespace Dorothy;
#include <ddraw.h>
#pragma comment(lib,"ddraw.lib")

static LPDIRECTDRAW g_pDD = NULL;

oScreen* oScreen::m_pkInstance = NULL;

oScreen::oScreen():
m_bVSync(false),
m_bZoomScreen(false),
m_fScaleX(1.0f),
m_fScaleY(1.0f),
m_iWidth(0),
m_iHeight(0),
m_iScreenWidth(0),
m_iScreenHeight(0),
m_iScaleWidth(0),
m_iScaleHeight(0),
m_pkScreenBuffer(NULL),
m_pkScaleBuffer(NULL),
m_pkBuffer(NULL)
{
	ZeroMemory(&m_kRect,sizeof(RECT));
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

oScreen::~oScreen()
{
	m_pkInstance = NULL;
	if (m_pkScreenBuffer != NULL)
	{
		delete [] m_pkScreenBuffer;
		m_pkScreenBuffer = NULL;
	}
	if (m_pkScaleBuffer != NULL)
	{
		delete [] m_pkScaleBuffer;
		m_pkScaleBuffer = NULL;
	}
	if(g_pDD != NULL)
	{
		g_pDD->Release();
		g_pDD = NULL;
	}
}

bool oScreen::Initialize(HANDLE hOutputHandle)
{
	if (hOutputHandle == 0)
	{
		return false;
	}
	oScreen::SetUpBuffer();
	return true;
}

void oScreen::SetUpBuffer()
{
	m_iScreenWidth = oConsole::GetInstance()->GetWidth();
	m_iScreenHeight = oConsole::GetInstance()->GetHeight();
	m_iBufferSize = m_iScreenWidth*m_iScreenHeight;
	m_iScaleWidth = (int)((float)m_iScreenWidth/m_fScaleX);
	m_iScaleHeight = (int)((float)m_iScreenHeight/m_fScaleY);
	m_kRect.right = m_kRect.left + m_iScaleWidth;
	m_kRect.bottom = m_kRect.top + m_iScaleHeight;
	if (m_pkScreenBuffer != NULL)
	{
		delete [] m_pkScreenBuffer;
	}
	m_pkScreenBuffer = new CHAR_INFO[m_iBufferSize]();
	if (m_pkScaleBuffer != NULL)
	{
		delete [] m_pkScaleBuffer;
	}
	m_pkScaleBuffer = new CHAR_INFO[m_iBufferSize*ZOOM_BUFFER_FACTOR]();
	oScreen::SetUpUsingBuffer();
}

void oScreen::Begin(oColor fillColor)
{
	if (oConsole::GetInstance()->GetWidth() != m_iScreenWidth
		|| oConsole::GetInstance()->GetHeight() != m_iScreenHeight)
	{
		oScreen::SetUpBuffer();
	}
	if (fillColor != COLOR_NONE)
	{
		int iSize = (m_bZoomScreen ? m_iBufferSize*ZOOM_BUFFER_FACTOR : m_iBufferSize);
		for (int i = 0;i < iSize;i++)
		{
			m_pkBuffer[i].Char.AsciiChar = 0;
			m_pkBuffer[i].Attributes = fillColor;
		}
	}
}

void oScreen::End()
{
	if (m_bZoomScreen)
	{
		for (int y = 0;y < m_iScreenHeight;y++)
		{
			int DstY = y*m_iScreenWidth;
			int SrcY = (int)((float)y/m_fScaleY)*m_iScaleWidth;
			for (int x = 0;x < m_iScreenWidth;x++)
			{
				m_pkScreenBuffer[DstY+x] = m_pkScaleBuffer[SrcY+(int)((float)x/m_fScaleX)];
			}
		}
	}
	COORD size = {(SHORT)m_iScreenWidth, (SHORT)m_iScreenHeight};
	if (m_bVSync)
	{
		g_pDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);
	}
	oConsole::GetInstance()->ShowScreen(m_pkScreenBuffer,size);
}

int oScreen::GetViewX()
{
	return m_kRect.left;
}

int oScreen::GetViewY()
{
	return m_kRect.top;
}

int oScreen::GetWidth()
{
	return m_iWidth;
}

int oScreen::GetHeight()
{
	return m_iHeight;
}

CHAR_INFO* oScreen::GetBuffer()
{
	return m_pkBuffer;
}

void oScreen::SetView( int X, int Y )
{
	m_kRect.left = X;
	m_kRect.top = Y;
	m_kRect.right = X + m_iScaleWidth;
	m_kRect.bottom = Y + m_iScaleHeight;
}

void oScreen::SetScale( float fScaleX, float fScaleY )
{
	if (fScaleX < MIN_SCREEN_SCALE)
	{
		fScaleX = MIN_SCREEN_SCALE;
	}
	if (fScaleY < MIN_SCREEN_SCALE)
	{
		fScaleY = MIN_SCREEN_SCALE;
	}
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
	m_bZoomScreen = ((fScaleX != 1.0f || fScaleY != 1.0f) ? true : false);
	m_iScaleWidth = (int)((float)m_iScreenWidth/fScaleX);
	if (fScaleX > 1.0f)
	{
		m_iScaleWidth++;
	}
	m_iScaleHeight = (int)((float)m_iScreenHeight/fScaleY);
	if (fScaleY > 1.0f)
	{
		m_iScaleHeight++;
	}
	m_kRect.right = m_kRect.left + m_iScaleWidth;
	m_kRect.bottom = m_kRect.top + m_iScaleHeight;
	oScreen::SetUpUsingBuffer();
}

void oScreen::SetUpUsingBuffer()
{
	if (m_bZoomScreen)
	{
		m_iWidth = m_iScaleWidth;
		m_iHeight = m_iScaleHeight;
		m_pkBuffer = m_pkScaleBuffer;
	}
	else
	{
		m_iWidth = m_iScreenWidth;
		m_iHeight = m_iScreenHeight;
		m_pkBuffer = m_pkScreenBuffer;
	}
}

oScreen* oScreen::GetInstance()
{
	return m_pkInstance;
}

const RECT* oScreen::GetRect()
{
	return &m_kRect;
}

oImage* oScreen::CaptureScreen()
{
	oImage* pkImage = new oImage();
	pkImage->Create(m_iScreenWidth,m_iScreenHeight);
	for (int y = 0;y < m_iScreenHeight;y++)
	{
		for (int x = 0;x < m_iScreenWidth;x++)
		{
			int pos = y*m_iScreenWidth+x;
			pkImage->SetColor(x,y,m_pkScreenBuffer[pos].Attributes);
			pkImage->SetChar(x,y,m_pkScreenBuffer[pos].Char.AsciiChar);
		}
	}
	return pkImage;
}

float oScreen::GetScaleX()
{
	return m_fScaleX;
}

float oScreen::GetScaleY()
{
	return m_fScaleY;
}

void oScreen::Put_Pixel( int X, int Y, oColor color, char ch )
{
	if (0 <= X && X < m_iWidth && 0 <= Y && Y < m_iHeight)
	{
		int n = m_iWidth*Y+X;
		m_pkBuffer[n].Attributes = color;
		m_pkBuffer[n].Char.AsciiChar = ch;
	}
}

void oScreen::DrawPoint( const oPoint* pointList, oUInt number, oColor color, char ch )
{
	for (oUInt n = 0;n < number;n++)
	{
		oScreen::Put_Pixel(pointList[n].x-m_kRect.left, pointList[n].y-m_kRect.top, color, ch);
	}
}

void oScreen::DrawLine( const oPoint& start,const oPoint& end, oColor color, char ch )
{
	short int x, y, deltaX, deltaY, halfCount, errorTerm, i, flag;
	oPoint sp = {(start.x - m_kRect.left), (start.y - m_kRect.top)};
	oPoint ep = {(end.x - m_kRect.left), (end.y - m_kRect.top)};
	deltaX = ep.x - sp.x;
	deltaY = ep.y - sp.y;
	if (abs(deltaY)<abs(deltaX))
	{
		if (deltaX<0)
		{
			i = sp.x; sp.x = ep.x; ep.x = i;
			i = sp.y; sp.y = ep.y; ep.y = i;
			deltaX = ep.x - sp.x;
			deltaY = ep.y - sp.y;
		}
		if (deltaY<0) flag = -1;else flag = 1;
		deltaY = abs(deltaY);
		halfCount = deltaX >> 1;
		errorTerm = 0;
		x = sp.x;
		y = sp.y;
		for (i = 0; i <= deltaX; i++)
		{
			oScreen::Put_Pixel(x,y,color,ch);
			x++;
			errorTerm = errorTerm + deltaY;
			if (errorTerm > halfCount)
			{
				errorTerm = errorTerm - deltaX;
				y = y + flag;
			}
		}
	}
	else
	{
		if (deltaY<0)
		{
			i = sp.x; sp.x = ep.x; ep.x = i;
			i = sp.y; sp.y = ep.y; ep.y = i;
			deltaX = ep.x - sp.x;
			deltaY = ep.y - sp.y;
		}
		if (deltaX<0) flag = -1; else flag = 1;
		deltaX = abs(deltaX);
		halfCount = deltaY >> 1;
		errorTerm = 0;
		x = sp.x;
		y = sp.y;
		for (i = 0; i <=deltaY; i++)
		{
			oScreen::Put_Pixel(x,y,color,ch);
			y++;
			errorTerm = errorTerm + deltaX;
			if (errorTerm > halfCount)
			{
				errorTerm = errorTerm - deltaY;
				x = x + flag;
			}
		}
	}
}

void oScreen::DrawRectangle( const RECT& rect, oColor color, char ch )
{
	int y0 = rect.top-m_kRect.top;
	int y1 = rect.bottom-m_kRect.top-1;
	for (int i = rect.left;i < rect.right;i++)
	{
		int posX = i-m_kRect.left;
		oScreen::Put_Pixel(posX,y0,color,ch);
		oScreen::Put_Pixel(posX,y1,color,ch);
	}
	int x0 = rect.left-m_kRect.left;
	int x1 = rect.right-m_kRect.left-1;
	for (int i = rect.top;i < rect.bottom;i++)
	{
		int posY = i-m_kRect.top;
		oScreen::Put_Pixel(x0,posY,color,ch);
		oScreen::Put_Pixel(x1,posY,color,ch);
	}
}

void oScreen::DrawCircle( const oPoint& center, int radius, oColor color, char ch )
{
	if (radius == 0)
	{
		oScreen::DrawPoint(&center,1,color);
	}
	else
	{
		oPoint point = {center.x, center.y+radius};
		int nodes = 360/(radius < 40 ? radius*9 : 360);
		for (int i = 1;i <= 360;i+=nodes)
		{
			float fx = (float)center.x+oSin(i)*radius;
			float fy = (float)center.y+oCos(i)*radius;
			oPoint temp = {oRoundToInt(fx), oRoundToInt(fy)};
			oScreen::DrawLine(point,temp,color,ch);
			point = temp;
		}
	}
}

bool oScreen::SetVSync( bool VSync )
{
	m_bVSync = VSync;
	if (VSync && g_pDD == NULL)
	{
		if (FAILED(DirectDrawCreate(NULL,&g_pDD,NULL)))
		{
			return false;
		}
		g_pDD->SetCooperativeLevel(oConsole::GetInstance()->GetWindowHandle(), DDSCL_NORMAL);
	}
	return true;
}

bool oScreen::IsVSync()
{
	return m_bVSync;
}