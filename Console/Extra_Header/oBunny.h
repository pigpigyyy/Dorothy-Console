#pragma once
#include "Dorothy.h"
using namespace Dorothy;
#include "oDataBase.h"
#include <stdlib.h>

enum oBunnyLevel
{
	LEVEL_ONE = 0,
	LEVEL_TWO,
	LEVEL_THREE,
	LEVEL_FOUR
};

enum oBunnyState
{
	BNY_NORMAL,
	BNY_ROTATE,
	BNY_SCALE,
	BNY_RUN,
	BNY_ANIM,
	BNY_NONE
};

typedef Delegate<void (oObject*)> oBunnyHandler;

class oBunny : public oSprite, public oIUpdate
{
public:
	oBunny(int originX = 0,int originY = 0);
	void SetOrigin(int originX,int originY);
	void SetLevel(oBunnyLevel level);
	void Stop();
	void Reset();
	void Refresh();
	//Actions below
	void StayHappy();
	void GoInsane();
	void BeGiantBunny();
	void Ah_Its_A_Rolling_World();
	//Actions above
	void PlayRightAnim();
	void PlayWrongAnim();
	virtual void Update();
	oBunnyHandler OnActFailed;
	oBunnyHandler OnActSucceeded;
	//delegate functions
	void MakeBunnyAct();
	void MakeBunnyJump();
	void BunnyRunAway();
	void ActionEnd(oAnimation* pkTarget);
protected:
	void RunBunny();
	oBunnyState m_State;
	oBunnyLevel m_Level;
	bool m_bSucceeded;
	int m_iCurrentFace;
	int m_iOffsetValue;
	int m_iOffsetY;
	int m_iOffsetX;
	int m_iOriginX;
	int m_iOriginY;
	oTimer m_kNormalTimer;
	oTimer m_kEventTimer;
	oTimer m_kRunTimer;
	oRotateAnimation m_kRotate;
	oScaleAnimation m_kScale;
	oFrameAnimation m_kRightFrame;
	oFrameAnimation m_kWrongFrame;
};