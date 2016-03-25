#include "oGame.h"
#include "oUpdateController.h"
#include "oRenderController.h"
using namespace Dorothy;

static oUpdateController g_kUpdateController;

static oRenderController g_kRenderController;

oGame* oGame::m_pkInstance = NULL;

oGame::oGame():
m_bRun(true),
m_pkConsole(NULL),
m_pkScreen(NULL),
m_pkInput(NULL),
m_pkSoundPlayer(NULL),
m_pkMusicPlayer(NULL){}

bool oGame::Initialize( const char* title, int iFPS,
					   bool bUseSound, bool bUseMusic,
					   int width, int height,
					   oUInt iFONT_WxH )
{
	m_pkConsole = new oConsole();
	if (!m_pkConsole->Initialize(width, height, iFONT_WxH))
	{
		return false;
	}
	m_pkConsole->ShowCursor(false);
	m_pkConsole->SetWindowTitle(title);
	m_pkScreen = new oScreen();
	if (!m_pkScreen->Initialize(m_pkConsole->GetOutputHandle()))
	{
		return false;
	}
	m_pkInput = new oInput();
	if (!m_pkInput->Initialize(m_pkConsole->GetInputHandle()))
	{
		return false;
	}
	if (bUseSound)
	{
		m_pkSoundPlayer = new oSoundPlayer();
		if (!m_pkSoundPlayer->Initialize(m_pkConsole->GetWindowHandle()))
		{
			return false;
		}
	}
	if (bUseMusic)
	{
		m_pkMusicPlayer = new oMusicPlayer();
	}
	m_iFPS = iFPS;
	HDC hDisplay = CreateDC("DISPLAY",NULL,NULL,NULL);
	int iDisplayWidth = GetDeviceCaps(hDisplay, HORZRES);
	int iDisplayHeight = GetDeviceCaps(hDisplay, VERTRES);
	DeleteDC(hDisplay);
	RECT kWinRect;
	GetWindowRect(m_pkConsole->GetWindowHandle(),&kWinRect);
	int iWinWidth = kWinRect.right - kWinRect.left;
	int iWinHeight = kWinRect.bottom - kWinRect.top;
	m_pkConsole->MoveWindow((iDisplayWidth>>1)-(iWinWidth>>1),
		(iDisplayHeight>>1)-(iWinHeight>>1));
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
	return true;
}

oGame::~oGame()
{
	if (m_pkInput != NULL)
	{
		delete m_pkInput;
		m_pkInput = NULL;
	}
	if (m_pkScreen != NULL)
	{
		delete m_pkScreen;
		m_pkScreen = NULL;
	}
	if (m_pkInput != NULL)
	{
		delete m_pkInput;
		m_pkInput = NULL;
	}
}

void oGame::Run()
{
	m_bRun = true;
	float fSPF = 1.0f/m_iFPS;
	m_kTimer.Start();
	while (m_bRun)
	{
		Sleep(0);
		float fRealTime = m_kTimer.GetCount();
		if (fRealTime >= fSPF)
		{
			m_kTimer.ZeroCount();
			if (oIUpdate::IsAutoManaged())
			{
				g_kUpdateController.Update();
			}
			else
			{
				this->Update();
			}
			if (oIRender::IsAutoManaged())
			{
				g_kRenderController.Render();
			}
			else
			{
				this->Render();
			}
			m_iCurrentFPS = oRoundToInt(1.0f / fRealTime);
		}
	}
}

void oGame::Stop()
{
	m_bRun = false;
}

int oGame::GetCurrentFPS()
{
	return m_iCurrentFPS;
}

int oGame::GetFPS()
{
	return m_iFPS;
}

void oGame::SetBackColor( oColor color )
{
	oRenderController::GetInstance()->SetBackColor(color);
}

oGame* oGame::GetInstance()
{
	return m_pkInstance;
}
