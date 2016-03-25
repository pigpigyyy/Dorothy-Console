#pragma once
#include <Windows.h>
#include <fstream>
using std::fstream;
using std::ios;
#include <dsound.h>
#include "oDataTypes.h"
#include "oSoundPlayer.h"

namespace Dorothy
{
	class DLLEXPORT oSound
	{
	public:
		oSound();
		~oSound();
		bool LoadFromFile(const char* filename);
		void SetVolume(oUInt32 iVolume);
		void Play(bool bLoop);
		void Stop();
		void Release();
	protected:
		oSoundBuffer* m_lpkSound;
	};
}