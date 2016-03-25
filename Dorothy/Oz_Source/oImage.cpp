#include "oImage.h"
using namespace Dorothy;

oImage::oImage():
m_iWidth(0),
m_iHeight(0),
m_ppData(NULL){}

oImage::~oImage()
{
	oImage::Release();
}

void oImage::Release()
{
	if (m_ppData != NULL)
	{
		for (int y = 0;y < m_iHeight;y++)
		{
			delete [] m_ppData[y];
			m_ppData[y] = NULL;
		}
		delete [] m_ppData;
		m_ppData = NULL;
		m_iHeight = 0;
		m_iWidth = 0;
	}
}

void oImage::Create( int width, int height )
{
	oImage::Release();
	m_iWidth = width;
	m_iHeight = height;
	m_ppData = new CHAR_INFO*[height];
	for (int i = 0;i < height;i++)
	{
		m_ppData[i] = new CHAR_INFO[width]();
	}
}

void oImage::SetChar( int x, int y, char ch )
{
	m_ppData[y][x].Char.AsciiChar = ch;
}

void oImage::SetColor( int x, int y, oColor color )
{
	m_ppData[y][x].Attributes = color;
}

char oImage::GetChar( int x, int y ) const
{
	return m_ppData[y][x].Char.AsciiChar;
}

oColor oImage::GetColor( int x, int y ) const
{
	return m_ppData[y][x].Attributes;
}

int oImage::GetWidth() const
{
	return m_iWidth;
}

int oImage::GetHeight() const
{
	return m_iHeight;
}

CHAR_INFO** oImage::GetData()
{
	return m_ppData;
}