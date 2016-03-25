#pragma once
#include <Windows.h>
#include <assert.h>
#include "oDataTypes.h"

typedef BOOL (WINAPI *PROCSETCONSOLEFONT)(HANDLE,DWORD);

namespace Dorothy
{
	class DLLEXPORT oConsole
	{
	public:
		oConsole();
		~oConsole();
		bool Initialize(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT,
			oUInt font = FONT_6x12);
		void SetWindowTitle(const char* title);
		void SetScreenSize(int width, int height);
		void MoveWindow(int ScrX,int ScrY);
		void SetFont(oUInt iFONT_WxH);
		void SetCursorPos(int x, int y);
		void SetCursorWidth(int percentWidth);
		void ShowCursor(bool visible);
		void ShowScreen(const CHAR_INFO* buffer, const COORD& size);
		int GetWidth();
		int GetHeight();
		HANDLE GetOutputHandle();
		HANDLE GetInputHandle();
		HWND GetWindowHandle();
		static oConsole* GetInstance();
	protected:
		HANDLE m_hOutput;
		HANDLE m_hInput;
		HWND m_hWindow;
		const static COORD m_kOrigin;
		COORD m_kScreenSize;
		SMALL_RECT m_kScreenRect;
		CONSOLE_CURSOR_INFO m_kCursor;
		static oConsole* m_pkInstance;
	};
}