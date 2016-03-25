#include "oScene.h"

oScene::oScene():
m_State(SS_STOP){}

oSceneState oScene::GetState()
{
	return SS_STOP;
}

oSceneID oScene::GetNextSceneID()
{
	return m_NextScene;
}