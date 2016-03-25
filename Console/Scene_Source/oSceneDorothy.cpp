#include "oSceneDorothy.h"

oSceneDorothy::oSceneDorothy():
m_kTimer(3000),
m_pkScreenShot(NULL)
{
	m_kTimer.OnTimer += std::make_pair(this, &oSceneDorothy::PlayScaleAnim);
	m_kRotate.OnEnd += std::make_pair(this, &oSceneDorothy::RotateEnd);
	m_kScaleBk.OnEnd += std::make_pair(this, &oSceneDorothy::ScaleBkEnd);
}

void oSceneDorothy::Begin()
{
	m_NextScene = SCENE_MENU;

	//万一开头这个Scene被反复播放就把它的内容清空重新初始化
	m_kGroup.Clear();
	//更新过的Dorothy 1.002标志
	oObject* pkFlag = new oObject();
	oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_FLAG);
	pkFlag->SetImage(pkImage);
	pkFlag->SetPosition(40,57);
	pkFlag->SetGroup(&m_kGroup);
	//初始化Dorothy
	oSprite* pkUnit = new oSprite(false);
	pkImage = oDataBase::GetSingleton()->GetImage(IMG_DOROTHY);
	pkUnit->SetImage(pkImage);
	RECT rc = {0,0,pkImage->GetWidth(),pkImage->GetHeight()};
	pkUnit->SetRenderRect(rc);
	pkUnit->SetSize(32,32);
	pkUnit->SetPosition(70,24);
	pkUnit->SetZIndex(0);
	pkUnit->SetGroup(&m_kGroup);
	//初始化Dorothy的旋转动画
	m_kRotate.SetTarget(pkUnit);
	m_kRotate.SetRotate(0,-360,2000);
	m_kRotate.SetLoop(false);
	m_kRotate.Start();
	//初始化Dorothy的Scale动画
	m_kScale.SetTarget(pkUnit);
	m_kScale.SetScale(1.0f,3.0f,1.0f,3.0f,500);
	m_kScale.SetReverse(true);
	m_kScale.SetLoop(false);
	m_kScale.Start();
	//初始化背景Scale的动画
	m_kScaleBk.SetScale(1.0f,0.0f,1.0f,0.0f,1000);
	//初始化Dorothy的字样
	pkUnit = new oSprite(false);
	pkImage = oDataBase::GetSingleton()->GetImage(IMG_DOROTHYTXT);
	pkUnit->SetImage(pkImage);
	rc.left = 0;rc.top = 0;rc.right = pkImage->GetWidth();rc.bottom = pkImage->GetHeight();
	pkUnit->SetRenderRect(rc);
	pkUnit->SetSize(rc.right<<1,rc.bottom);
	pkUnit->SetPosition(48,59);
	pkUnit->SetScale(2.0f,1.0f);
	pkUnit->SetZIndex(1);
	pkUnit->SetGroup(&m_kGroup);

	m_State = SS_RUN;
}

oSceneState oSceneDorothy::Update()
{
	switch (m_State)
	{
	case SS_PAUSE:
		return SS_RUN;
	case SS_RUN:
		return SS_RUN;
	case SS_END:
		m_State = SS_STOP;
		return SS_END;
	default:
		return SS_STOP;
	}
}

void oSceneDorothy::Render()
{
	oScreen::GetInstance()->Begin(BACK_WHITEI|FORE_WHITEI);
	m_kGroup.Render();
	oScreen::GetInstance()->End();
}

oSceneDorothy::~oSceneDorothy()
{
	m_kGroup.Clear();
}

void oSceneDorothy::PlayScaleAnim()
{
	m_kGroup.Clear();
	oSprite* pkUnit = new oSprite(false);
	m_pkScreenShot = oScreen::GetInstance()->CaptureScreen();
	RECT rc = {0,0,m_pkScreenShot->GetWidth(),m_pkScreenShot->GetHeight()};
	pkUnit->SetImage(m_pkScreenShot);
	pkUnit->SetRenderRect(rc);
	pkUnit->SetSize(m_pkScreenShot->GetWidth(),m_pkScreenShot->GetHeight());
	pkUnit->SetPosition(0,0);
	pkUnit->SetGroup(&m_kGroup);
	m_kScaleBk.SetTarget(pkUnit);
	m_kScaleBk.Start();
}

void oSceneDorothy::RotateEnd( oAnimation* pkTarget )
{
	m_kTimer.Start();
	oDataBase::GetSingleton()->GetSound(SND_MEOMEO)->Play(false);
}

void oSceneDorothy::ScaleBkEnd( oAnimation* pkTarget )
{
	delete m_pkScreenShot;
	m_pkScreenShot = NULL;
	m_State = SS_END;
}