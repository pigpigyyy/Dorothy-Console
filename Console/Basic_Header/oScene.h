#pragma once
#include "Dorothy.h"
using namespace Dorothy;

#define TOTALSCENES 4

enum oSceneID
{
	SCENE_DOROTHY = 0,
	SCENE_MENU,
	SCENE_README,
	SCENE_GAME
};

enum oSceneState
{
	SS_RUN,
	SS_PAUSE,
	SS_END,
	SS_STOP
};

class oScene
{
public:
	oScene();
	virtual void Begin() = 0;
	virtual oSceneState Update() = 0;
	virtual void Render() = 0;
	oSceneState GetState();
	oSceneID GetNextSceneID();
protected:
	oSceneID m_NextScene;
	oSceneState m_State;
};