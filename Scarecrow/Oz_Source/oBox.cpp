#include "oBox.h"
using namespace Scarecrow;
#include "Box2D/Box2D.h"

oBox::oBox(oImage* pkImage):
m_bUpdateRender(true),
m_bUpdatePos(true),
m_fSinA(0.0f),
m_fCosA(1.0f),
m_iAngle(0),
m_iRenderWidth(0),
m_iRenderHeight(0),
m_pkBody(NULL)
{
	ZeroMemory(&m_kImgRect,sizeof(oRect));
	oObject::SetImage(pkImage);
	m_iRenderWidth = pkImage->GetWidth();
	m_iRenderHeight = pkImage->GetHeight();
	oObject::SetSize(m_iRenderWidth, m_iRenderHeight);
	oIUpdate::Register();
}

oBox::~oBox()
{
	b2World* pkWorld = (b2World*)oPhysicWorld::GetInstance()->GetWorld();
	pkWorld->DestroyBody((b2Body*)m_pkBody);
}

void oBox::SetPosition( int X, int Y )
{
	m_bUpdatePos = true;
	m_kRect.x = X;
	m_kRect.y = Y;
}

void oBox::SetAngle( int iAngle )
{
	m_iAngle = iAngle;
	m_bUpdateRender = true;
	m_fSinA = oSin(iAngle);
	m_fCosA = oCos(iAngle);
}

void oBox::UpdateRenderData()
{
	int SrcWidth = m_iRenderWidth;
	int SrcHeight = m_iRenderHeight;
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

void oBox::Render()
{
	if (m_bUpdateRender)
	{
		m_bUpdateRender = false;
		oBox::UpdateRenderData();
		m_bUpdatePos = true;
	}
	if (m_bUpdatePos)
	{
		m_bUpdatePos = false;
		m_kImgRect.x = m_kRect.x+(m_kRect.w>>1)-(m_kImgRect.w>>1);
		m_kImgRect.y = m_kRect.y+(m_kRect.h>>1)-(m_kImgRect.h>>1);
	}
	if (!oIRender::IsVisible())
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
			int srcX = oRoundToInt((x + m_fRotMinWidth) * m_fCosA + (y + m_fRotMinHeight) * m_fSinA); 
			int srcY = oRoundToInt((y + m_fRotMinHeight) * m_fCosA - (x + m_fRotMinWidth) * m_fSinA);
 			if((srcX >= 0) && (srcX < m_iRenderWidth) && (srcY >= 0) && (srcY < m_iRenderHeight)) 
			{
				int PosX = x+tmpX;
				if (ppImage[srcY][srcX].Attributes != COLOR_NONE)
				{
					pBuffer[PosY*W+PosX] = ppImage[srcY][srcX];
				}
				else if (ppImage[srcY][srcX].Char.AsciiChar != 0)
				{
					pBuffer[PosY*W+PosX].Char.AsciiChar = ppImage[srcY][srcX].Char.AsciiChar;
				}
			}
		}
	}
}

oColor oBox::GetDisplayColor( int X, int Y ) const
{
	X -= m_kImgRect.x;
	Y -= m_kImgRect.y;
	int srcX = oRoundToInt(((X + m_fRotMinWidth) * m_fCosA + (Y + m_fRotMinHeight) * m_fSinA)); 
	int srcY = oRoundToInt(((Y + m_fRotMinHeight) * m_fCosA - (X + m_fRotMinWidth) * m_fSinA));
	if ((srcX >= 0) && (srcX < m_iRenderWidth) &&(srcY >= 0) && (srcY < m_iRenderHeight))
	{
		return m_pkImage->GetColor(srcX,srcY);
	}
	return COLOR_NONE;
}

char oBox::GetDisplayChar( int X, int Y ) const
{
	X -= m_kImgRect.x;
	Y -= m_kImgRect.y;
	int srcX = oRoundToInt(((X + m_fRotMinWidth) * m_fCosA + (Y + m_fRotMinHeight) * m_fSinA)); 
	int srcY = oRoundToInt(((Y + m_fRotMinHeight) * m_fCosA - (X + m_fRotMinWidth) * m_fSinA));
	if( (srcX >= 0) && (srcX < m_iRenderWidth) &&(srcY >= 0) && (srcY < m_iRenderHeight)) 
	{
		return m_pkImage->GetChar(srcX,srcY);
	}
	return 0;
}

int oBox::GetAngle() const
{
	return m_iAngle;
}

void oBox::Update()
{
	float fAngle = ((b2Body*)m_pkBody)->GetAngle();
	oBox::SetAngle(oR2D(fAngle));
	b2Vec2 kVec2 = ((b2Body*)m_pkBody)->GetPosition();
	oObject::SetPosition(
		oDoroValue(kVec2.x) - (m_iRenderWidth>>1),
		oDoroValue(kVec2.y) - (m_iRenderHeight>>1));
}

void oBox::SetVelocity( int Vx, int Vy )
{
	((b2Body*)m_pkBody)->SetLinearVelocity(b2Vec2(oB2Value(Vx),oB2Value(Vy)));
}

void oBox::ApplyForce( int x, int y, int iAngle, int iPower )
{
	b2Vec2 kForce;
	kForce.Set(iPower*oCos(-iAngle), iPower*oSin(-iAngle));
	b2Vec2 kPos = ((b2Body*)m_pkBody)->GetWorldPoint(
		b2Vec2(oB2Value(x-m_iRenderWidth/2), oB2Value(y-m_iRenderHeight/2)));
	((b2Body*)m_pkBody)->ApplyForce(kForce, kPos);
}
