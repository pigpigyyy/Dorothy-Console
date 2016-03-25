#include "oMusicPlayer.h"
using namespace Dorothy;
#define SAFE_RELEASE(p) { if (p) {(p)->Release();(p)=NULL;} }
#define V_RETURN(x) { if (FAILED(x)) {return false;} }

static REFTIME g_fDuration;
static IBasicAudio* g_pAudio = NULL;
static IGraphBuilder* g_pBuilder = NULL;
static IMediaControl* g_pControl = NULL;
static IMediaPosition* g_pPos = NULL;

oMusicPlayer* oMusicPlayer::m_pkInstance = NULL;

oMusicPlayer::oMusicPlayer():
m_State(PS_STOP)
{
	CoInitialize(NULL);
	m_pkInstance = this;
}

oMusicPlayer::~oMusicPlayer()
{
	Close();
	CoUninitialize();
}

bool oMusicPlayer::Open( const char *filename )
{
	CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC, IID_IGraphBuilder, (void**)&g_pBuilder);
	V_RETURN(g_pBuilder->QueryInterface(IID_IMediaControl, (void**)&g_pControl));
	V_RETURN(g_pBuilder->QueryInterface(IID_IMediaPosition, (void**)&g_pPos));
	V_RETURN(g_pBuilder->QueryInterface(IID_IBasicAudio, (void**)&g_pAudio));
	WCHAR wfilename[MAX_PATH] = {0};
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, MAX_PATH);
	V_RETURN(g_pBuilder->RenderFile(wfilename, NULL));
	g_pPos->put_CurrentPosition(0);
	g_pPos->get_Duration(&g_fDuration);
	return true;
}

void oMusicPlayer::Close()
{
	m_State = PS_STOP;
	SAFE_RELEASE(g_pAudio);
	SAFE_RELEASE(g_pControl);
	SAFE_RELEASE(g_pPos);
	SAFE_RELEASE(g_pBuilder);
}

void oMusicPlayer::Play()
{
	if (m_State != PS_PAUSE)
	{
		g_pPos->put_CurrentPosition(0);
	}
	g_pControl->Run();
	m_State = PS_PLAY;
}

void oMusicPlayer::Pause()
{
	m_State = PS_PAUSE;
	g_pControl->Pause();
}

void oMusicPlayer::Stop()
{
	m_State = PS_STOP;
	g_pControl->Stop();
}

void oMusicPlayer::SetVolume( oUInt iVolume )
{
	g_pAudio->put_Volume(iVolume == 0 ? -10000 : -30*(100-iVolume));
}

oPlayerState oMusicPlayer::GetState()
{
	double fCurrent;
	g_pPos->get_CurrentPosition(&fCurrent);
	if (fCurrent == g_fDuration)
	{
		m_State = PS_STOP;
	}
	return m_State;
}

oMusicPlayer* oMusicPlayer::GetInstance()
{
	assert(m_pkInstance);
	return m_pkInstance;
}