#include "oSceneGame.h"

static RECT g_BkRect[2] =
{
	{0,0,180,90},
	{0,90,180,180}
};

static RECT g_kLevelRect[4] =
{
	{0,0,297,64},
	{0,0,338,64},
	{0,0,379,64},
	{0,0,420,64}
};

oSceneGame::oSceneGame():
m_kLevelTimer(47000,4),
m_kScoreTimer(12000),
m_iLevel(0)
{
	m_kLevelTimer.OnTimer += std::make_pair(this, &oSceneGame::MakeLevelUp);
	m_kScoreTimer.OnTimer += std::make_pair(this, &oSceneGame::StartSceneEnd);
	m_kScaleScorePage.OnEnd += std::make_pair(this, &oSceneGame::ScaleScoreEnd);
}

oSceneGame::~oSceneGame()
{
	m_kGroup.Clear();
}

void oSceneGame::Begin()
{
	m_iScore = 0;
	m_iLevel = LEVEL_ONE;
	m_NextScene = SCENE_MENU;

	if (m_kGroup.GetItems().size() == 0)
	{
		//初始化Level图片
		oSprite* pkLevelImage = new oSprite(true);
		oImage* pkImage = oDataBase::GetSingleton()->GetImage(IMG_LEVEL);
		pkLevelImage->SetImage(pkImage);
		pkLevelImage->SetRenderRect(g_kLevelRect[0]);
		pkLevelImage->SetPosition(180,13);
		pkLevelImage->SetZIndex(0);
		pkLevelImage->SetDetective(false);
		m_pkLevelImage = pkLevelImage;
		pkLevelImage->SetGroup(&m_kGroup);
		//初始化背景图片
		oSprite* pkGameBk = new oSprite();
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_GAMEBK);
		pkGameBk->SetImage(pkImage);
		pkGameBk->SetRenderRect(g_BkRect[0]);
		pkGameBk->SetPosition(0,0);
		pkGameBk->SetSize(180,90);
		pkGameBk->SetZIndex(0);
		pkGameBk->SetDetective(false);
		pkGameBk->SetGroup(&m_kGroup);
		//初始化兔子们
		for (int i = 0;i < BUNNY_HALF_NUM;i++)
		{
			oBunny* pkBunny = new oBunny(41+i*27,15);
			pkBunny->SetZIndex(1);
			pkBunny->SetLevel(LEVEL_ONE);
			pkBunny->OnActSucceeded += std::make_pair(this, &oSceneGame::DecreaseScore);
			pkBunny->OnActFailed += std::make_pair(this, &oSceneGame::IncreaseScore);
			pkBunny->SetGroup(&m_kGroup);
			m_ppkBunny[i] = pkBunny;
			pkBunny = new oBunny(41+i*27,50);
			pkBunny->SetZIndex(1);
			pkBunny->SetLevel(LEVEL_ONE);
			pkBunny->OnActSucceeded += std::make_pair(this, &oSceneGame::DecreaseScore);
			pkBunny->OnActFailed += std::make_pair(this, &oSceneGame::IncreaseScore);
			pkBunny->SetGroup(&m_kGroup);
			m_ppkBunny[i+4] = pkBunny;
		}
		//初始化分数
		oNumber* pkNumber = new oNumber();
		pkNumber->SetPosition(147,6);
		pkNumber->SetZIndex(2);
		pkNumber->SetGroup(&m_kGroup);
		m_pkNumber = pkNumber;
		//初始化返回按钮
		m_pkButton = new oButton(BT_RETURN);
		m_pkButton->SetPosition(151,73);
		m_pkButton->SetZIndex(2);
		m_pkButton->OnClick += std::make_pair(this, &oSceneGame::ReturnButtonClick);
		m_pkButton->RotateAnimation.OnEnd += std::make_pair(this, &oSceneGame::ButtonAnimEnd);
		m_pkButton->SetGroup(&m_kGroup);
		//初始化得分背景图片
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_SCORE);
		m_kScoreBkImage.SetImage(pkImage);
		m_kScoreBkImage.SetPosition(0,0);
		//初始化得分界面图片
		m_kScorePage.SetPosition(0,0);
		m_kScorePage.SetSize(180,90);
		//初始化得分界面Scale动画
		m_kScaleScorePage.SetScale(1.0f,0.0f,1.0f,0.0f,1000);
		m_kScaleScorePage.SetTarget(&m_kScorePage);
		//初始化背景动画
		m_kBkFrame.SetUpFrame(2);
		m_kBkFrame.SetFrame(0,g_BkRect[0],360);
		m_kBkFrame.SetFrame(1,g_BkRect[1],360);
		m_kBkFrame.SetLoop(true);
		m_kBkFrame.SetTarget(pkGameBk);
		m_kBkFrame.Start();
	}
	else
	{
		m_pkNumber->SetNumber(m_iScore);
		for (int i = 0;i < BUNNY_NUM;i++)
		{
			m_ppkBunny[i]->Refresh();
			m_ppkBunny[i]->SetLevel(LEVEL_ONE);
		}
		m_pkLevelImage->SetRenderRect(g_kLevelRect[LEVEL_ONE]);
		m_pkLevelImage->SetPosition(180,13);
		m_pkNumber->SetPosition(147,6);
	}
	oMusicPlayer::GetInstance()->Open("Music/Nya.mp3");
	oMusicPlayer::GetInstance()->Play();
	m_kLevelTimer.Start();

	m_State = SS_RUN;
}

oSceneState oSceneGame::Update()
{
	switch (m_State)
	{
	case SS_PAUSE:
		return SS_RUN;
	case SS_RUN:
		m_kGroup.Update();
		//Level图片移动
		if (m_pkLevelImage->GetX() > -420)
		{
			m_pkLevelImage->SetPosition(m_pkLevelImage->GetX()-1,m_pkLevelImage->GetY());
		}
		return SS_RUN;
	case SS_END:
		m_State = SS_STOP;
		return SS_END;
	default:
		return SS_STOP;
	}
}

void oSceneGame::Render()
{
	oScreen::GetInstance()->Begin(BACK_WHITEI);
	//如果没有播放结尾动画就正常绘图
	if (!m_kScaleScorePage.IsPlaying())
	{
		//如果没在看最后的得分画面就绘制游戏画面
		if (!m_kScoreTimer.IsRunning())
		{
			m_kGroup.Render();
		}
		else
		{
			m_kScoreBkImage.Render();
			m_pkNumber->Render();
		}
	}
	//否则绘制结尾动画
	else
	{
		m_kScorePage.Render();
	}
	oScreen::GetInstance()->End();
}

void oSceneGame::IncreaseScore(oObject* pkBunny)
{
	m_iScore += 15;
	m_pkNumber->SetNumber(m_iScore);
}

void oSceneGame::DecreaseScore(oObject* pkBunny)
{
	m_iScore -= 15;
	if (m_iScore < 0)
	{
		m_iScore = 0;
	}
	m_pkNumber->SetNumber(m_iScore);
}

void oSceneGame::EndGame()
{
	m_kLevelTimer.Stop();
	oMusicPlayer::GetInstance()->Close();
	m_NextScene = SCENE_MENU;
	m_State = SS_END;
}

void oSceneGame::MakeLevelUp()
{
	m_iLevel++;
	if (m_iLevel > LEVEL_FOUR)
	{
		for (int i = 0;i < BUNNY_NUM;i++)
		{
			m_ppkBunny[i]->Reset();
		}
		oMusicPlayer::GetInstance()->SetVolume(50);
		m_pkNumber->SetPosition(71,16);
		m_kScoreTimer.Start();
	}
	else
	{
		for (int i = 0;i < BUNNY_NUM;i++)
		{
			m_ppkBunny[i]->SetLevel((oBunnyLevel)m_iLevel);
		}
		m_pkLevelImage->SetRenderRect(g_kLevelRect[m_iLevel]);
		m_pkLevelImage->SetPosition(180,13);
	}
}

void oSceneGame::StartSceneEnd()
{
	oImage* pkImage = oScreen::GetInstance()->CaptureScreen();
	m_kScorePage.SetImage(pkImage);
	RECT rc = {0,0,pkImage->GetWidth(),pkImage->GetHeight()};
	m_kScorePage.SetRenderRect(rc);
	m_kScaleScorePage.Start();
}

void oSceneGame::ButtonAnimEnd(oAnimation* pkTarget)
{
	oSceneGame::EndGame();
}

void oSceneGame::ReturnButtonClick( oObject* pkButton )
{
	for (int i = 0;i < BUNNY_NUM;i++)
	{
		m_ppkBunny[i]->Stop();
	}
	m_State = SS_PAUSE;
}

void oSceneGame::ScaleScoreEnd( oAnimation* pkTarget )
{
	oImage* pkImage = m_kScorePage.GetImage();
	delete pkImage;
	oSceneGame::EndGame();
}
