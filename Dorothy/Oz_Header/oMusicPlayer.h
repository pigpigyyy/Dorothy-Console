#pragma once
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <dshow.h>
#include <assert.h>
#include "oDataTypes.h"
#pragma comment( lib, "Strmiids.lib")
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "Ole32.lib" )

namespace Dorothy
{
	enum oPlayerState{PS_PLAY,PS_PAUSE,PS_STOP};
	class DLLEXPORT oMusicPlayer
	{
	public:
		oMusicPlayer();
		~oMusicPlayer();
		bool Open(const char* filename);
		void Close();
		void Play();
		void Pause();
		void Stop();
		void SetVolume(oUInt iVolume);
		oPlayerState GetState();
		static oMusicPlayer* GetInstance();
	protected:
		oPlayerState m_State;
		static oMusicPlayer* m_pkInstance;
	};
}