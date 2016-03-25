#include "oBunnyGame.h"

bool oBunnyGame::Initialize()
{
	srand((oUInt)time(NULL));
	oIUpdate::SetAutoManaged(true);
	oIRender::SetAutoManaged(false);
	if (!oGame::Initialize(
		"Bunny Bunny Harmony!",
		FPS,
		true,
		true,
		180,
		90,
		FONT_3x5))
	{
		return false;
	}
	if (!m_kDataBase.Load())
	{
		return false;
	}
	//在下面生成所有场景
	m_pkSceneList[SCENE_DOROTHY] = new oSceneDorothy();//0
	m_pkSceneList[SCENE_MENU] = new oSceneMenu();//1
	m_pkSceneList[SCENE_README] = new oSceneReadme();//2
	m_pkSceneList[SCENE_GAME] = new oSceneGame();//3
	m_pkCurrentScene = m_pkSceneList[SCENE_DOROTHY];
	m_pkCurrentScene->Begin();
	oIUpdate::Register();
	return true;
}

void oBunnyGame::Update()
{
	oSceneState State = m_pkCurrentScene->Update();
	switch (State)
	{
	case SS_END:
		{
			int iSubscript = (int)m_pkCurrentScene->GetNextSceneID();
			m_pkCurrentScene = m_pkSceneList[iSubscript];
			m_pkCurrentScene->Begin();
		}
		break;
	case SS_STOP:
		oGame::Stop();
		break;
	default:
		break;
	}
}

void oBunnyGame::Render()
{
	m_pkCurrentScene->Render();
}

void oBunnyGame::Release()
{
	m_kDataBase.Unload();
	for (int i = 0;i < TOTALSCENES;i++)
	{
		delete m_pkSceneList[i];
		m_pkSceneList[i] = NULL;
	}
}