#pragma once
#include "Dorothy.h"
using namespace Dorothy;
#include "oDataBase.h"
#include <stdlib.h>
#include <math.h>

#define NUMBER_LEN 3//4 in fact
#define SCALE_NUM 4
class oNumber : public oSprite
{
public:
	oNumber(int iNumber = 0);
	void SetNumber(int iNumber);
	virtual void SetPosition(int X, int Y);
	virtual void Render();
	//delegate function
	void PlayAnim();
protected:
	oTimer m_kTimer;
	int GetDigitAt(int iSubscript);
	int m_iNumber;
	oScaleAnimation m_kScales[SCALE_NUM];
	oSprite m_kNumber[NUMBER_LEN];
};