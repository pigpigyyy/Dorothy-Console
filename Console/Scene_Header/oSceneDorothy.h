#pragma once
#include "oScene.h"
#include "oDataBase.h"

class oSceneDorothy : public oScene
{
public:
	oSceneDorothy();
	~oSceneDorothy();
	virtual void Begin();
	virtual oSceneState Update();
	virtual void Render();
	//delegate functions
	void PlayScaleAnim();
	void RotateEnd(oAnimation* pkTarget);
	void ScaleBkEnd(oAnimation* pkTarget);
private:
	oTimer m_kTimer;
	oImage* m_pkScreenShot;
	oGroup m_kGroup;
	oRotateAnimation m_kRotate;
	oScaleAnimation m_kScale;
	oScaleAnimation m_kScaleBk;
};
