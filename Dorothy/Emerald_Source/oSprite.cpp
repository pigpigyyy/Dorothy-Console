#include "oSprite.h"
using namespace Dorothy;

oSprite::oSprite( bool bImageBased ):
m_bImageBased(bImageBased),
m_bUpdateRender(true),
m_bUpdatePos(true),
m_fSinA(0.0f),
m_fCosA(1.0f),
m_fScaleX(1.0f),
m_fScaleY(1.0f),
m_bFlipX(false),
m_bFlipY(false),
m_iAngle(0),
m_iRenderWidth(0),
m_iRenderHeight(0)
{
	ZeroMemory(&m_kRenderRect,sizeof(RECT));
	ZeroMemory(&m_kImgRect,sizeof(oRect));
}

void oSprite::SetPosition( int X, int Y )
{
	m_bUpdatePos = true;
	m_kRect.x = X;
	m_kRect.y = Y;
}

void oSprite::SetSize( int width, int height )
{
	if (m_bImageBased && m_pkImage != NULL)
	{
		m_bUpdateRender = true;
		m_fScaleX = (float)m_iRenderWidth/width;
		m_fScaleY = (float)m_iRenderHeight/height;
	}
	oObject::SetSize(width, height);
}

void oSprite::SetScale( float fScaleX, float fScaleY )
{
	if (m_pkImage != NULL)
	{
		m_bUpdateRender = true;
		if (fScaleX < 0)
		{
			m_bFlipX = true;
			fScaleX = -fScaleX;
		}
		else
		{
			m_bFlipX = false;
			if (fScaleX == 0)
			{
				fScaleX = 0.000001f;
			}
		}
		m_fScaleX = 1.0f/fScaleX;
		if (fScaleY < 0)
		{
			m_bFlipY = true;
			fScaleY = -fScaleY;
		}
		else
		{
			m_bFlipY = false;
			if (fScaleY == 0)
			{
				fScaleY = 0.000001f;
			}
		}
		m_fScaleY = 1.0f/fScaleY;
		if (m_bImageBased)
		{
			oObject::SetSize((int)((float)m_iRenderWidth*fScaleX),(int)((float)m_iRenderHeight*fScaleY));
		}
	}
}

void oSprite::SetAngle( int iAngle )
{
	if (m_pkImage != NULL)
	{
		m_bUpdateRender = true;
		m_iAngle = iAngle;
		m_fSinA = oSin(-iAngle);
		m_fCosA = oCos(-iAngle);
	}
}

void oSprite::SetRenderRect( const RECT& rect )
{
	if (m_pkImage != NULL)
	{
		m_bUpdateRender = true;
		memcpy(&m_kRenderRect,&rect,sizeof(RECT));
		m_iRenderWidth = m_kRenderRect.right - m_kRenderRect.left;
		m_iRenderHeight = m_kRenderRect.bottom - m_kRenderRect.top;
		if (m_bImageBased)
		{
			oObject::SetSize((int)((float)m_iRenderWidth/m_fScaleX),(int)((float)m_iRenderHeight/m_fScaleY));
		}
	}
}

void oSprite::UpdateRenderData()
{
	//SrcWidth,SrcHeight为Scale处理后的宽高
	int SrcWidth = (int)((m_bImageBased ? m_kRect.w : (float)m_iRenderWidth/m_fScaleX) + 0.5f);
	int SrcHeight = (int)((m_bImageBased ? m_kRect.h : (float)m_iRenderHeight/m_fScaleY) + 0.5f);
	float x1 = -SrcHeight * m_fSinA; 
	float y1 = SrcHeight * m_fCosA; 
	float x2 = SrcWidth * m_fCosA - SrcHeight * m_fSinA; 
	float y2 = SrcHeight * m_fCosA + SrcWidth * m_fSinA; 
	float x3 = SrcWidth * m_fCosA;
	float y3 = SrcWidth * m_fSinA;
	m_fRotMinWidth = (x3 > (x1 > x2 ? x2 : x1) ? (x1 > x2 ? x2 : x1) : x3); 
	m_fRotMinWidth = (m_fRotMinWidth > 0 ? 0 : m_fRotMinWidth); 
	m_fRotMinHeight = (y3 > (y1 > y2 ? y2 : y1) ? (y1 > y2 ? y2 : y1) : y3); 
	m_fRotMinHeight = (m_fRotMinHeight > 0 ? 0 : m_fRotMinHeight); 
	float maxWidth = (x3 > (x1 > x2 ? x1 : x2) ? x3 : (x1 > x2 ? x1 : x2)); 
	maxWidth = (maxWidth > 0 ? maxWidth : 0); 
	float maxHeight = (y3 > (y1 > y2 ? y1 : y2) ? y3 : (y1 > y2 ? y1 : y2)); 
	maxHeight = (maxHeight > 0 ? maxHeight : 0); 
	m_kImgRect.w = (int)(maxWidth - m_fRotMinWidth + 0.5f); 
	m_kImgRect.h = (int)(maxHeight - m_fRotMinHeight + 0.5f);
}

void oSprite::Render()
{
	if (m_bUpdateRender)
	{
		m_bUpdateRender = false;
		oSprite::UpdateRenderData();
		m_bUpdatePos = true;
	}
	if (m_bUpdatePos)
	{
		m_bUpdatePos = false;
		m_kImgRect.x = m_kRect.x+(m_kRect.w>>1)-(m_kImgRect.w>>1);
		m_kImgRect.y = m_kRect.y+(m_kRect.h>>1)-(m_kImgRect.h>>1);
	}
	if (m_pkImage == NULL || !oIRender::IsVisible())
	{
		return;
	}
	const RECT* pkRect = oScreen::GetInstance()->GetRect();
	if (m_kImgRect.x+m_kImgRect.w <= pkRect->left
		|| m_kImgRect.y+m_kImgRect.h <= pkRect->top
		|| m_kImgRect.y >= pkRect->bottom
		|| m_kImgRect.x >= pkRect->right)
	{
		return;
	}
	int W = oScreen::GetInstance()->GetWidth();
	CHAR_INFO* pBuffer = oScreen::GetInstance()->GetBuffer();
	CHAR_INFO** ppImage = m_pkImage->GetData();
	int tmp = pkRect->left - m_kImgRect.x;
	int sX = tmp > 0 ? tmp : 0;
	tmp = pkRect->top - m_kImgRect.y;
	int sY = tmp > 0 ? tmp : 0;
	tmp = m_kImgRect.x + m_kImgRect.w - pkRect->right;
	int eX = tmp > 0 ? m_kImgRect.w-tmp : m_kImgRect.w;
	tmp = m_kImgRect.y + m_kImgRect.h - pkRect->bottom;
	int eY = tmp > 0 ? m_kImgRect.h -tmp : m_kImgRect.h;
	int tmpX = m_kImgRect.x - pkRect->left;
	int tmpY = m_kImgRect.y - pkRect->top;
	for (int y = sY;y < eY;y++)
	{
		int PosY = y+tmpY;
		for (int x = sX;x < eX;x++)
		{
			int srcX = oRoundToInt(((x + m_fRotMinWidth) * m_fCosA + (y + m_fRotMinHeight) * m_fSinA) * m_fScaleX); 
			int srcY = oRoundToInt(((y + m_fRotMinHeight) * m_fCosA - (x + m_fRotMinWidth) * m_fSinA) * m_fScaleY);
			if( (srcX >= 0) && (srcX < m_iRenderWidth) &&(srcY >= 0) && (srcY < m_iRenderHeight)) 
			{
				int PosX = x+tmpX;
				int imgY = (m_bFlipY ? m_iRenderHeight-srcY-1 : srcY)+m_kRenderRect.top;
				int imgX = (m_bFlipX ? m_iRenderWidth-srcX-1 : srcX)+m_kRenderRect.left;
				if (ppImage[imgY][imgX].Attributes != COLOR_NONE)
				{
					pBuffer[PosY*W+PosX] = ppImage[imgY][imgX];
				}
				else if (ppImage[imgY][imgX].Char.AsciiChar != 0)
				{
					pBuffer[PosY*W+PosX].Char.AsciiChar = ppImage[imgY][imgX].Char.AsciiChar;
				}
			}
		}
	}
}

oColor oSprite::GetDisplayColor( int X, int Y ) const
{
	if (m_pkImage == NULL)
	{
		return COLOR_NONE;
	}
	X -= m_kImgRect.x;
	Y -= m_kImgRect.y;
	int srcX = oRoundToInt(((X + m_fRotMinWidth) * m_fCosA + (Y + m_fRotMinHeight) * m_fSinA) * m_fScaleX); 
	int srcY = oRoundToInt(((Y + m_fRotMinHeight) * m_fCosA - (X + m_fRotMinWidth) * m_fSinA) * m_fScaleY);
	if ((srcX >= 0) && (srcX < m_iRenderWidth) &&(srcY >= 0) && (srcY < m_iRenderHeight))
	{
		return m_pkImage->GetColor(srcX,srcY);
	}
	return COLOR_NONE;
}

char oSprite::GetDisplayChar( int X, int Y ) const
{
	if (m_pkImage == NULL)
	{
		return 0;
	}
	X -= m_kImgRect.x;
	Y -= m_kImgRect.y;
	int srcX = oRoundToInt(((X + m_fRotMinWidth) * m_fCosA + (Y + m_fRotMinHeight) * m_fSinA) * m_fScaleX); 
	int srcY = oRoundToInt(((Y + m_fRotMinHeight) * m_fCosA - (X + m_fRotMinWidth) * m_fSinA) * m_fScaleY);
	if( (srcX >= 0) && (srcX < m_iRenderWidth) &&(srcY >= 0) && (srcY < m_iRenderHeight)) 
	{
		return m_pkImage->GetChar(srcX,srcY);
	}
	return 0;
}

const oRect* oSprite::GetRect() const
{
	if (m_bImageBased)
	{
		return &m_kImgRect;
	}
	else
	{
		return &m_kRect;
	}
}

float oSprite::GetScaleX() const
{
	return 1.0f/m_fScaleX;
}

float oSprite::GetScaleY() const
{
	return 1.0f/m_fScaleY;
}

int oSprite::GetAngle() const
{
	return m_iAngle;
}
