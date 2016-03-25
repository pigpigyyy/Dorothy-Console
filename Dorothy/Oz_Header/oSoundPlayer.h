#pragma once
#include <Windows.h>
#include <dsound.h>
#include <assert.h>
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oSoundPlayer
	{
	public:
		oSoundPlayer();
		~oSoundPlayer();
		bool Initialize(HWND hWindow);
		oSoundDevice* GetDevice();
		static oSoundPlayer* GetInstance();
	protected:
		oSoundDevice* m_lpkDSound;
		static oSoundPlayer *m_pkInstance;
	};
}