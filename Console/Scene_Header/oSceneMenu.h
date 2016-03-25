#pragma once
#include "oScene.h"
#include "oDataBase.h"
#include "oBack.h"
#include "oButton.h"

#define BUTTON_NUM 3
class oSceneMenu : public oScene
{
public:
	oSceneMenu();
	~oSceneMenu();
	virtual void Begin();
	virtual oSceneState Update();
	virtual void Render();
	//delegate functions
	void PlayerSelect(oObject* pkTarget);
	void TurnToSelectScene(oAnimation* pkTarget);
private:
	oButton* m_pkButton[BUTTON_NUM];
	oTimer m_kTimer;
	oGroup m_kGroup;
};