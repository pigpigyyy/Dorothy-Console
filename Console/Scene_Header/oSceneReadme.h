#pragma once
#include "oScene.h"
#include "oDataBase.h"
#include "oButton.h"
#include "oFlower.h"

#define FLOWER_NUM 5
class oSceneReadme : public oScene
{
public:
	oSceneReadme();
	~oSceneReadme();
	virtual void Begin();
	virtual oSceneState Update();
	virtual void Render();
	//delegate functions
	void ReturnToMenu(oAnimation* pkTarget);
protected:
	oButton* m_pkButton;
	oGroup m_kGroup;
};