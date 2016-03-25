#include "oNumber.h"

static RECT g_kNumberRect[10] =
{
	{0,0,5,8},
	{6,0,11,8},
	{12,0,17,8},
	{18,0,23,8},
	{24,0,29,8},
	{30,0,35,8},
	{36,0,41,8},
	{42,0,47,8},
	{48,0,53,8},
	{54,0,59,8}
};

oNumber::oNumber(int iNumber) :
	m_iNumber(iNumber),
	m_kTimer(2000, 0)
{
	oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_NUMBERS);
	oSprite::SetImage(pkImage);
	oSprite::SetDetective(false);
	oSprite::SetSize(5, 8);
	m_kScales[3].SetTarget(this);
	for (int i = 0; i < NUMBER_LEN; i++)
	{
		m_kNumber[i].SetImage(pkImage);
		m_kNumber[i].SetDetective(false);
		m_kNumber[i].SetSize(5, 8);
		m_kScales[i].SetTarget(&m_kNumber[i]);
	}
	oNumber::SetNumber(iNumber);
	for (int i = 0; i < SCALE_NUM; i++)
	{
		m_kScales[i].SetScale(1.0f, 3.0f, 1.0f, 3.0f, 500);
		m_kScales[i].SetReverse(true);
	}
	m_kTimer.OnTimer += std::make_pair(this, &oNumber::PlayAnim);
	m_kTimer.Start();
}

void oNumber::SetNumber(int iNumber)
{
	m_iNumber = iNumber;
	int iDigit = oNumber::GetDigitAt(3);
	oSprite::SetRenderRect(g_kNumberRect[iDigit]);
	for (int i = 0; i < NUMBER_LEN; i++)
	{
		iDigit = oNumber::GetDigitAt(2 - i);
		m_kNumber[i].SetRenderRect(g_kNumberRect[iDigit]);
	}
}

int oNumber::GetDigitAt(int iSubscript)
{
	int iPow = (int)pow(10.0f, iSubscript);
	int iDigit = (m_iNumber % (iPow * 10)) / iPow;
	return iDigit;
}

void oNumber::Render()
{
	oSprite::Render();
	for (int i = 0; i < NUMBER_LEN; i++)
	{
		m_kNumber[i].Render();
	}
}

void oNumber::SetPosition(int X, int Y)
{
	oSprite::SetPosition(X, Y);
	for (int i = 0; i < NUMBER_LEN; i++)
	{
		m_kNumber[i].SetPosition(X + (i + 1) * 6, Y);
	}
}

void oNumber::PlayAnim()
{
	int iRand = rand() % 4;
	m_kScales[iRand].Start();
}
