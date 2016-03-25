#include "oObject.h"
#include "oGroup.h"
using namespace Dorothy;

oObject::oObject():
m_bDetective(true),
m_pkImage(NULL),
m_pkPrev(NULL),
m_pkNext(NULL),
m_pkGroup(NULL)
{
	ZeroMemory(&m_kRect,sizeof(RECT));
}

oObject::~oObject()
{
	m_pkImage = NULL;
	oObject::RemoveGroup();
}

void oObject::SetPosition( int X, int Y )
{
	m_kRect.x = X;
	m_kRect.y = Y;
}

void oObject::SetSize( int width, int height )
{
	m_kRect.w = width;
	m_kRect.h = height;
}

void oObject::Render()
{
	if (m_pkImage == NULL || !oIRender::IsVisible())
	{
		return;
	}
	int eX = m_pkImage->GetWidth();
	int eY = m_pkImage->GetHeight();
	const RECT* pkRect = oScreen::GetInstance()->GetRect();
	if (m_kRect.x+eX <= pkRect->left
		|| m_kRect.y+eY <= pkRect->top
		|| m_kRect.y >= pkRect->bottom
		|| m_kRect.x >= pkRect->right)
	{
		return;
	}
	int W = oScreen::GetInstance()->GetWidth();
	CHAR_INFO* pBuffer = oScreen::GetInstance()->GetBuffer();
	CHAR_INFO** ppImage = m_pkImage->GetData();
	int tmp = pkRect->left-m_kRect.x;
	int sX = tmp > 0 ? tmp : 0;
	tmp = pkRect->top-m_kRect.y;
	int sY = tmp > 0 ? tmp : 0;
	tmp = m_kRect.x+eX-pkRect->right;
	eX = tmp > 0 ? eX-tmp : eX;
	tmp = m_kRect.y+eY-pkRect->bottom;
	eY = tmp > 0 ? eY-tmp : eY;
	tmp = m_kRect.x-pkRect->left;
	int tmpY = m_kRect.y-pkRect->top;
	for (int y = sY;y < eY;y++)
	{
		int PosY = y+tmpY;
		for (int x = sX;x < eX;x++)
		{
			if (ppImage[y][x].Attributes != COLOR_NONE)
			{
				pBuffer[PosY*W+x+tmp] = ppImage[y][x];
			}
			else if (ppImage[y][x].Char.AsciiChar != 0)
			{
				pBuffer[PosY*W+x+tmp].Char.AsciiChar = ppImage[y][x].Char.AsciiChar;
			}
		}
	}
}

void oObject::SetImage( oImage* image )
{
	m_pkImage = image;
}

oImage* oObject::GetImage() const
{
	return m_pkImage;
}

int oObject::GetX() const
{
	return m_kRect.x;
}

int oObject::GetY() const
{
	return m_kRect.y;
}

int oObject::GetWidth() const
{
	return m_kRect.w;
}

int oObject::GetHeight() const
{
	return m_kRect.h;
}

oColor oObject::GetDisplayColor( int X, int Y ) const
{
	if (m_pkImage == NULL)
	{
		return COLOR_NONE;
	}
	X -= m_kRect.x;
	Y -= m_kRect.y;
	if (X >= 0 && X < m_pkImage->GetWidth() && Y >= 0 && Y < m_pkImage->GetHeight())
	{
		return m_pkImage->GetColor(X,Y);
	}
	return COLOR_NONE;
}

char oObject::GetDisplayChar( int X, int Y ) const
{
	if (m_pkImage == NULL)
	{
		return 0;
	}
	X -= m_kRect.x;
	Y -= m_kRect.y;
	if (X >= 0 && X < m_pkImage->GetWidth() && Y >= 0 && Y < m_pkImage->GetHeight())
	{
		return m_pkImage->GetChar(X,Y);
	}
	return 0;
}

const oRect* oObject::GetRect() const
{
	return &m_kRect;
}

void oObject::SetDetective( bool bDetective )
{
	m_bDetective = bDetective;
}

bool oObject::IsDetective() const
{
	return m_bDetective;
}

void oObject::SetGroup( oGroup* group )
{
	if (group == m_pkGroup)
	{
		return;
	}
	oObject::RemoveGroup();
	if (group != NULL)
	{
		if (group->m_pkFirst == NULL)
		{
			group->m_pkFirst = this;
			group->m_pkLast = this;
		}
		else
		{
			m_pkPrev = group->m_pkLast;
			group->m_pkLast->m_pkNext = this;
			group->m_pkLast = this;
		}
		m_pkGroup = group;
	}
}

oGroup* oObject::GetGroup() const
{
	return m_pkGroup;
}

oObject* oObject::Next() const
{
	return m_pkNext;
}

void oObject::RemoveGroup()
{
	if (m_pkGroup != NULL)
	{
		if (m_pkPrev == NULL)
		{
			m_pkGroup->m_pkFirst = m_pkNext;
			if (m_pkNext) m_pkNext->m_pkPrev = NULL;
		}
		else
		{
			m_pkPrev->m_pkNext = m_pkNext;
			if (m_pkNext) m_pkNext->m_pkPrev = m_pkPrev;
		}
		if (m_pkNext == NULL)
		{
			m_pkGroup->m_pkLast = m_pkPrev;
			if (m_pkPrev) m_pkPrev->m_pkNext = NULL;
		}
		else
		{
			m_pkNext->m_pkPrev = m_pkPrev;
			if (m_pkPrev) m_pkPrev->m_pkNext = m_pkNext;
		}
		m_pkPrev = NULL;
		m_pkNext = NULL;
		m_pkGroup = NULL;
	}
}

oObject* oObject::Prev() const
{
	return m_pkPrev;
}