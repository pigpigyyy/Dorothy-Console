#pragma once
#include <Windows.h>
#include "oDataTypes.h"
#include "oScreen.h"
#include "oIUpdate.h"

namespace Dorothy
{
	enum oWheelState{WH_UP,WH_DOWN,WH_NONE};
	class DLLEXPORT oInput:public oIUpdate
	{
	public:
		oInput();
		bool Initialize(HANDLE hInputHandle);
		bool GetKeyState(oUInt8 iVK_KEY);
		bool IsKeyUp(oUInt8 iVK_KEY);
		bool IsKeyDown(oUInt8 iVK_KEY);
		bool IsLeftMouseDown();
		bool IsRightMouseDown();
		bool IsLeftMouseUp();
		bool IsRightMouseUp();
		bool GetLeftMouseState();
		bool GetRightMouseState();
		bool IsDoubleClicked();
		bool IsWheelUp();
		bool IsWheelDown();
		int GetMouseX();
		int GetMouseY();
		int GetMouseScreenX();
		int GetMouseScreenY();
		static oInput* GetInstance();
	private:
		virtual void Update();
		bool m_bLeftPrev;
		bool m_bLeftDown;
		bool m_bRightPrev;
		bool m_bRightDown;
		bool m_bDoubleClick;
		bool m_bKeyPrev[MAX_KEY_TYPE];
		bool m_bKeyDown[MAX_KEY_TYPE];
		int m_iPosX;
		int m_iPosY;
		int m_iLastKey[MAX_INPUT_READ];
		int m_iLastKeyCount;
		HANDLE m_hInput;
		DWORD m_iEvent;
		DWORD m_iReadInput;
		oWheelState m_WheelState;
		INPUT_RECORD m_kInputBuffer[MAX_INPUT_READ];
		static oInput* m_pkInstance;
	};
}