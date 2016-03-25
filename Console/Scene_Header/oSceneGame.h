#pragma once
#include "oScene.h"
#include "oDataBase.h"
#include "oBunny.h"
#include "oNumber.h"
#include "oButton.h"

#define BUNNY_NUM 8
#define BUNNY_HALF_NUM 4

class oSceneGame:public oScene
{
public:
	oSceneGame();
	~oSceneGame();
	virtual void Begin();
	virtual oSceneState Update();
	virtual void Render();
	//delegate functions
	void MakeLevelUp();
	void StartSceneEnd();
	void ReturnButtonClick(oObject* pkButton);
	void ButtonAnimEnd(oAnimation* pkTarget);
	void ScaleScoreEnd(oAnimation* pkTarget);
	void IncreaseScore(oObject* pkBunny);
	void DecreaseScore(oObject* pkBunny);
protected:
	void EndGame();
	int m_iLevel;
	int m_iScore;
	oTimer m_kLevelTimer;
	oTimer m_kScoreTimer;
	oFrameAnimation m_kBkFrame;
	oBunny* m_ppkBunny[BUNNY_NUM];
	oNumber* m_pkNumber;
	oButton* m_pkButton;
	oSprite* m_pkLevelImage;
	oObject m_kScoreBkImage;
	oSprite m_kScorePage;
	oGroup m_kGroup;
	oScaleAnimation m_kScaleScorePage;
};