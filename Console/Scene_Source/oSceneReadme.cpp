#include "oSceneReadme.h"

static vector<oObject*> g_kList;

oSceneReadme::oSceneReadme():
m_pkButton(NULL){}

void oSceneReadme::Begin()
{
	m_NextScene = SCENE_MENU;

	if (m_kGroup.GetItems().size() == 0)
	{
		//初始化返回按钮
		m_pkButton = new oButton(BT_RETURN);
		m_pkButton->SetPosition(139,70);
		m_pkButton->SetZIndex(2);
		m_pkButton->RotateAnimation.OnEnd += std::make_pair(this, &oSceneReadme::ReturnToMenu);
		m_pkButton->SetGroup(&m_kGroup);
		//初始化说明文字的图片
		oObject* pkText = new oObject();
		oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_README);//Readme.bmp
		pkText->SetImage(pkImage);
		pkText->SetPosition(0,0);
		pkText->SetZIndex(1);
		pkText->SetDetective(false);
		pkText->SetGroup(&m_kGroup);
		//初始化花朵
		oFlower* pkFlowerlist[5];
		for (int i = 0;i < 5;i++)
		{
			pkFlowerlist[i] = new oFlower();
			pkFlowerlist[i]->SetZIndex(0);
			pkFlowerlist[i]->SetGroup(&m_kGroup);
		}
		pkFlowerlist[0]->SetPosition(55,22);
		pkFlowerlist[1]->SetPosition(106,8);
		pkFlowerlist[2]->SetPosition(19,77);
		pkFlowerlist[3]->SetPosition(122,72);
		pkFlowerlist[4]->SetPosition(79,50);
	}

	m_State = SS_RUN;
}

oSceneState oSceneReadme::Update()
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

void oSceneReadme::Render()
{
	oScreen::GetInstance()->Begin(BACK_WHITEI);
	m_kGroup.Render();
	oScreen::GetInstance()->End();
}

oSceneReadme::~oSceneReadme()
{
	m_kGroup.Clear();
}

void oSceneReadme::ReturnToMenu( oAnimation* pkTarget )
{
	m_NextScene = SCENE_MENU;
	m_State = SS_END;
}
