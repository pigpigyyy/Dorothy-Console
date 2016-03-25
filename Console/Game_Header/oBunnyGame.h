#pragma once
#include "oGameScenes.h"
#include <stdlib.h>
#include <time.h>

#define FPS 30

class oBunnyGame:public oGame
{
public:
	bool Initialize();
	virtual void Update();
	virtual void Render();
	void Release();
private:
	oDataBase m_kDataBase;
	oScene* m_pkSceneList[TOTALSCENES];
	oScene* m_pkCurrentScene;
};
