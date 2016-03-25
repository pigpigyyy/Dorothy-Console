#include "oSceneMenu.h"

oSceneMenu::oSceneMenu():
m_kTimer(300){}

void oSceneMenu::Begin()
{
	m_NextScene = SCENE_DOROTHY;

	if (m_kGroup.GetItems().size() == 0)
	{
		//初始化背景动画
		oBack* pkBack = new oBack();
		pkBack->SetZIndex(0);
		pkBack->SetMove(144,-144);
		pkBack->SetGroup(&m_kGroup);
		pkBack = new oBack();
		pkBack->SetZIndex(0);
		pkBack->SetMove(0,288);
		pkBack->SetGroup(&m_kGroup);
		//初始化按钮
		m_pkButton[0] = new oButton(BT_START);
		m_pkButton[0]->SetPosition(15,27);
		m_pkButton[0]->SetZIndex(1);
		m_pkButton[0]->SetGroup(&m_kGroup);
		m_pkButton[1] = new oButton(BT_INSTRUCTION);
		m_pkButton[1]->SetPosition(33,44);
		m_pkButton[1]->SetZIndex(3);
		m_pkButton[1]->SetGroup(&m_kGroup);
		m_pkButton[2] = new oButton(BT_QUIT);
		m_pkButton[2]->SetPosition(49,61);
		m_pkButton[2]->SetZIndex(4);
		m_pkButton[2]->SetGroup(&m_kGroup);
		for (int i = 0;i < BUTTON_NUM;i++)
		{
			m_pkButton[i]->OnClick += std::make_pair(this, &oSceneMenu::PlayerSelect);
			m_pkButton[i]->RotateAnimation.OnEnd += std::make_pair(this, &oSceneMenu::TurnToSelectScene);
		}
	}
	else
	{
		for (int i = 0;i < BUTTON_NUM;i++)
		{
			m_pkButton[i]->SetDetective(true);
		}
	}

	m_State = SS_RUN;
}

oSceneState oSceneMenu::Update()
{
	switch (m_State)
	{
	case SS_RUN:
		m_kGroup.Update();
		return SS_RUN;
	case SS_END:
		m_State = SS_STOP;
		return SS_END;
	default:
		return SS_STOP;
	}
}

void oSceneMenu::Render()
{
	oScreen::GetInstance()->Begin(BACK_WHITEI);
	m_kGroup.Render();
	oScreen::GetInstance()->End();
}

oSceneMenu::~oSceneMenu()
{
	m_kGroup.Clear();
}

void oSceneMenu::PlayerSelect( oObject* pkTarget )
{
	for (int i = 0;i < BUTTON_NUM;i++)
	{
		m_pkButton[i]->SetDetective(false);
	}
}

void oSceneMenu::TurnToSelectScene( oAnimation* pkTarget )
{
	if (pkTarget == &(m_pkButton[0]->RotateAnimation))
	{
		m_NextScene = SCENE_GAME;
		m_State = SS_END;
	}
	else if (pkTarget == &(m_pkButton[1]->RotateAnimation))
	{
		m_NextScene = SCENE_README;
		m_State = SS_END;
	}
	else if (pkTarget == &(m_pkButton[2]->RotateAnimation))
	{
		m_State = SS_STOP;
	}
}