/*
#include "Scarecrow.h"
using namespace Scarecrow;

class oPickBox:public oIUpdate
{
public:
	void Start()
	{
		m_kLine.SetColor(BACK_CYANI);
		m_kLine.SetZIndex(100);
		oIUpdate::Register();
	}
	void Stop()
	{
		m_kPicker.Drop();
	}
protected:
	virtual void Update()
	{
		if (!m_kPicker.IsPicking())
		{
			if (oInput::GetInstance()->IsLeftMouseDown())
			{
				oPoint pos = {
					oInput::GetInstance()->GetMouseX(),
					oInput::GetInstance()->GetMouseY()
				};
				if (m_kPicker.Pick(pos) != NULL)
				{
					m_kLine.SetLine(pos,pos);
					m_kLine.SetVisible(true);
				}
			}
		}
		else
		{
			oPoint pos = {
				oInput::GetInstance()->GetMouseX(),
				oInput::GetInstance()->GetMouseY()
			};
			m_kPicker.Move(pos);
			oPoint start,end;
			m_kPicker.GetJointLine(start,end);
			m_kLine.SetLine(start,end);
			if (oInput::GetInstance()->IsLeftMouseUp())
			{
				m_kPicker.Drop();
				m_kLine.SetVisible(false);
			}
		}
	}
private:
	oBoxPicker m_kPicker;
	oLinePaint m_kLine;
};

#define FPS 30

class oMyGame:public oGame,oIUpdate
{
public:
	oMyGame(){}

	bool Initialize()
	{
		if (!oGame::Initialize(
			"Dorothy Physics",
			FPS,
			false,
			false,
			160,
			90,
			FONT_3x5))
		{
			return false;
		}
		oIUpdate::Register();
		oGame::SetBackColor(BACK_BLACK);
		oScreen::GetInstance()->SetVSync(true);
		m_pkWorld = new oPhysicWorld(0.0f, 10.0f, oGame::GetFPS());

		m_pkImgFlandre = oCreateImageFromBMP24("Flandre.bmp");
		m_kImgBox.Create(20,20);
		for (int i = 0;i < 20;i++)
		{
			for (int j = 0;j < 20;j++)
			{
				if (i == 1 || i == 18 || i == 0 || i == 19
					|| j == 0 || j == 19 || j == 1 || j == 18)
				{
					m_kImgBox.SetColor(j,i,BACK_BLACK);
				}
				else
				{
					m_kImgBox.SetColor(j,i,BACK_CYANI);
				}
			}
		}
		oPoint kCenter = {90,40};
		m_kCircle.Set(kCenter,40,BACK_YELLOWI);
		m_kCircle.SetZIndex(99);

		oBoxInfo kInfo;
		kInfo.bDynamic = true;
		kInfo.fFraction = 0.3f;
		kInfo.fRestitution = 0.4f;
		kInfo.fDensity = 1.0f;
		oBox* pkBox;
		pkBox = oBoxFactory::CreateCircleBox(m_pkImgFlandre, 14, 0, kInfo);
		pkBox->SetGroup(&m_kGroup);
		pkBox = oBoxFactory::CreateCircleBox(m_pkImgFlandre, 40, 0, kInfo);
		pkBox->SetGroup(&m_kGroup);
		m_kCamera.LockAt(pkBox);
		pkBox = oBoxFactory::CreateCircleBox(m_pkImgFlandre, 70, 0, kInfo);
		pkBox->SetGroup(&m_kGroup);
		pkBox = oBoxFactory::CreateRectBox(&m_kImgBox, 0, 20, kInfo);
		pkBox->SetGroup(&m_kGroup);

		m_pkImgDorothy = oCreateImageFromBMP24("DorothyBack.bmp");
		m_kDorothyBack.SetImage(m_pkImgDorothy);
		m_kDorothyBack.SetPosition(0,0);

		m_pkWorld->AttachEdge(0,0,738,0);
		m_pkWorld->AttachEdge(0,0,0,210);
		m_pkWorld->AttachEdge(0,210,738,210);
		m_pkWorld->AttachEdge(738,0,738,210);

		m_kPick.Start();
		return true;
	}

	virtual void Update()
	{
		if (oInput::GetInstance()->IsLeftMouseDown())
		{
			oPoint pos = 
			{
				oInput::GetInstance()->GetMouseX(),
				oInput::GetInstance()->GetMouseY()
			};
			m_kCircle.SetCenter(pos);
		}
		if (oInput::GetInstance()->IsKeyDown(VK_ESCAPE))
		{
			oGame::Stop();
		}
	}

	void Release()
	{
		for (oObject* pkObj = m_kGroup.Last();pkObj != NULL;)
		{
			oObject* pkTemp = pkObj;
			pkObj = pkObj->Prev();
			delete pkTemp;
		}
		oReleaseImage(m_pkImgFlandre);
		oReleaseImage(m_pkImgDorothy);
		delete m_pkWorld;
		m_pkWorld = NULL;
	}
private:
	oPickBox m_kPick;
	oImage* m_pkImgFlandre;
	oImage m_kImgBox;
	oImage* m_pkImgDorothy;
	oCirclePaint m_kCircle;
	oObject m_kDorothyBack;
	oPhysicWorld* m_pkWorld;
	oCamera m_kCamera;
	oGroup m_kGroup;
};

int main()
{
	oMyGame kGame;
	kGame.Initialize();
	kGame.Run();
	kGame.Release();
	return 0;
}*/

/*
#include "Dorothy.h"
using namespace Dorothy;

#define FPS 30

class oMyGame:public oGame,oIUpdate
{
public:

	bool Initialize()
	{
		if (!oGame::Initialize(
			"Dorothy Physics",
			FPS,
			false,
			false,
			160,
			80,
			FONT_3x5))
		{
			return false;
		}
		oScreen::GetInstance()->SetVSync(true);
		oGame::SetBackColor(BACK_RED);
		oIUpdate::Register();

		oImage* pkImage = oCreateImageFromBMP24("Flandre.bmp");
		RECT rc = {0,0,pkImage->GetWidth(),pkImage->GetHeight()};

		oSprite* pkSprite = new oSprite(true);
		pkSprite->SetImage(pkImage);
		pkSprite->SetRenderRect(rc);
		pkSprite->SetPosition(0,0);
		pkSprite->SetZIndex(3);

		m_pkSprite = new oSprite();
		m_pkSprite->SetImage(pkImage);
		m_pkSprite->SetRenderRect(rc);
		m_pkSprite->SetSize(rc.right,rc.bottom);
		m_pkSprite->SetScale(10.0f,10.0f);
		m_pkSprite->SetAngle(-45);
		m_pkSprite->SetPosition(80,40);
		m_pkSprite->SetZIndex(2);

		m_pkTimer = new oTimer(1000);
		m_pkTimer->OnTimer += std::make_pair(this, &oMyGame::Collapse);
		m_pkTimer->Start();
		return true;
	}

	void Collapse()
	{
		m_pkSprite->SetVisible(V_COLLAPSE);
		m_pkTimer->OnTimer -= std::make_pair(this, &oMyGame::Collapse);
		m_pkTimer->OnTimer += std::make_pair(this, &oMyGame::Visible);
		m_pkTimer->Start();
	}

	void Visible()
	{
		m_pkSprite->SetVisible(V_VISIBLE);
		m_pkTimer->OnTimer -= std::make_pair(this, &oMyGame::Visible);
		m_pkTimer->OnTimer += std::make_pair(this, &oMyGame::Collapse);
		m_pkTimer->Start();
	}

	virtual void Update()
	{
		if (oInput::GetInstance()->IsKeyDown(VK_ESCAPE))
		{
			oGame::Stop();
		}
	}

private:
	oTimer* m_pkTimer;
	oSprite* m_pkSprite;
};

int main()
{
	oMyGame kGame;
	kGame.Initialize();
	kGame.Run();
	return 0;
}
*/

/*
#include "Dorothy.h"
using namespace Dorothy;

class MySprite:public oSprite,oIUpdate
{
public:
	MySprite()
	{
		oIUpdate::Register();
	}

	virtual void Update()
	{
		if (oInput::GetInstance()->GetKeyState(VK_UP))
		{
			oSprite::SetPosition(GetX(),GetY()-1);
		}
		if (oInput::GetInstance()->GetKeyState(VK_DOWN))
		{
			oSprite::SetPosition(GetX(),GetY()+1);
		}
		if (oInput::GetInstance()->GetKeyState(VK_LEFT))
		{
			oSprite::SetPosition(GetX()-1,GetY());
		}
		if (oInput::GetInstance()->GetKeyState(VK_RIGHT))
		{
			oSprite::SetPosition(GetX()+1,GetY());
		}
	}
};

class MyGame:public oGame,oIUpdate
{
public:
	bool Initialize()
	{
		if (!oGame::Initialize("Game",60,false,false,160,80,FONT_3x5))
			return false;
		oGame::SetBackColor(BACK_RED);
		oScreen::GetInstance()->SetVSync(true);
		oIUpdate::Register();
		m_pkImage = oCreateImageFromBMP24("Flandre.bmp");
		m_pkSprite = new MySprite();
		m_pkSprite->SetImage(m_pkImage);
		RECT rc = {0,0,m_pkImage->GetWidth(),m_pkImage->GetHeight()};
		m_pkSprite->SetRenderRect(rc);
		m_pkSprite->SetSize(rc.right,rc.bottom);
		m_pkSprite->SetPosition(0,0);
		m_kRotate.SetRotate(0,360,4000);
		m_kRotate.SetLoop(true);
		m_kRotate.SetTarget(m_pkSprite);
		m_kRotate.Start();
		return true;
	}

	virtual void Update()
	{
		if (oInput::GetInstance()->GetKeyState(VK_ESCAPE))
		{
			oGame::Stop();
		}
	}
private:
	oImage* m_pkImage;
	MySprite* m_pkSprite;
	oRotateAnimation m_kRotate;
};

int main()
{
	MyGame kGame;
	kGame.Initialize();
	kGame.Run();
	return 0;
}
*/

#include "Dorothy.h"
using namespace Dorothy;
#include "oBunnyGame.h"

int main()
{
	oBunnyGame kGame;
	kGame.Initialize();
	kGame.Run();
	return 0;
}
