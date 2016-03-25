#include "oSoundPlayer.h"
using namespace Dorothy;

oSoundPlayer *oSoundPlayer::m_pkInstance = NULL;

oSoundPlayer * oSoundPlayer::GetInstance()
{
	return m_pkInstance;
}

oSoundPlayer::oSoundPlayer()
{
	m_lpkDSound = NULL;
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

oSoundPlayer::~oSoundPlayer()
{
	if (NULL != m_lpkDSound)
	{
		((LPDIRECTSOUND8)m_lpkDSound)->Release();
		m_lpkDSound = NULL;
	}
	m_pkInstance = NULL;
}

bool oSoundPlayer::Initialize( HWND hWindow )
{
	/*创建DirectSound对象*/
	DirectSoundCreate8(NULL,(LPDIRECTSOUND8*)(&m_lpkDSound),NULL);
	if (NULL == m_lpkDSound)
	{
		return false;
	}
	/*设置协作级别*/
	if (FAILED(((LPDIRECTSOUND8)m_lpkDSound)->SetCooperativeLevel(hWindow,DSSCL_NORMAL)))
	{
		return false;
	}
	return true;
}

void* oSoundPlayer::GetDevice()
{
	return m_lpkDSound;
}