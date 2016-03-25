#pragma once
#include "oIRender.h"
#include "oIUpdate.h"
#include "oConsole.h"
#include "oScreen.h"
#include "oInput.h"
#include "oSoundPlayer.h"
#include "oMusicPlayer.h"
#include "oAccurateTimer.h"

namespace Dorothy
{
	class DLLEXPORT oGame : public oIRender, public oIUpdate
	{
	public:
		oGame();
		~oGame();
		bool Initialize(
			const char* title,
			int iFPS,
			bool bUseSound = false,
			bool bUseMusic = false,
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT,
			oUInt iFONT_WxH = FONT_8x16);
		void Run();
		void Stop();
		int GetFPS();
		int GetCurrentFPS();
		void SetBackColor(oColor color);
		static oGame* GetInstance();
	private:
		bool m_bRun;
		int m_iFPS;
		int m_iCurrentFPS;
		oConsole* m_pkConsole;
		oScreen* m_pkScreen;
		oInput* m_pkInput;
		oSoundPlayer* m_pkSoundPlayer;
		oMusicPlayer* m_pkMusicPlayer;
		oAccurateTimer m_kTimer;
		static oGame* m_pkInstance;
	};
}