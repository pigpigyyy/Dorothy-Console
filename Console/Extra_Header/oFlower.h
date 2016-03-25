#pragma once
#include "Dorothy.h"
using namespace Dorothy;
#include "oDataBase.h"
#include <stdlib.h>

class oFlower:public oSprite, public oIUpdate
{
public:
	oFlower();
	virtual void Update();
protected:
	COORD m_kVector;
	oFrameAnimation m_kFrame;
};