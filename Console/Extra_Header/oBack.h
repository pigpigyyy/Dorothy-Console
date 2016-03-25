#pragma once
#include "Dorothy.h"
using namespace Dorothy;
#include "oDataBase.h"

class oBack:public oSprite
{
public:
	oBack();
	void SetMove(int YFrom, int YTo);
protected:
	int m_iYFrom;
	int m_iYTo;
	oMoveAnimation m_kMove;
	oScaleAnimation m_kScale;
};