#pragma once
#include "Other/AcfDelegate.h"
using Acf::Delegate;
#include "Dorothy.h"
using namespace Dorothy;
#include "oDataBase.h"

enum oButtonType
{
	BT_NONE,
	BT_START,
	BT_INSTRUCTION,
	BT_QUIT,
	BT_RETURN
};

typedef Delegate<void (oObject*)> oButtonClickHandler;

class oButton:public oSprite, public oIUpdate
{
public:
	oButton(oButtonType type);
	oButtonClickHandler OnClick;
	oRotateAnimation RotateAnimation;
	virtual void Update();
	//delegate function
	void Reset(oAnimation* pkTarget);
protected:
	RECT* m_pkRect;
	oButtonType m_Type;
	oFrameAnimation m_kFrame;
};
