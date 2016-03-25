#pragma once
#include "oDataTypes.h"
#include "oConsole.h"
#include "oImage.h"
#include "math.h"

namespace Dorothy
{
	class DLLEXPORT oScreen
	{
	public:
		oScreen();
		~oScreen();
		bool Initialize(HANDLE hOutputHandle);
		void Begin(oColor fillColor = BACK_BLACK);
		void End();
		void DrawPoint(const oPoint* pointList, oUInt number, oColor color, char ch = ' ');
		void DrawLine(const oPoint& start, const oPoint& end, oColor color, char ch = ' ');
		void DrawRectangle(const RECT& rect, oColor color, char ch = ' ');
		void DrawCircle(const oPoint& center, int radius, oColor color, char ch = ' ');
		bool SetVSync(bool bVSync);
		//设置在Game World坐标系中自己左上角的位置
		void SetView(int X, int Y);
		void SetScale(float fScaleX, float fScaleY);
		int GetViewX();
		int GetViewY();
		float GetScaleX();
		float GetScaleY();
		int GetWidth();
		int GetHeight();
		bool IsVSync();
		oImage* CaptureScreen();
		CHAR_INFO* GetBuffer();
		const RECT* GetRect();
		static oScreen* GetInstance();
	protected:
		inline void Put_Pixel(int X, int Y, oColor color, char ch);
		void SetUpBuffer();
		void SetUpUsingBuffer();
		bool m_bVSync;
		bool m_bZoomScreen;
		float m_fScaleX;
		float m_fScaleY;
		int m_iWidth;
		int m_iHeight;
		int m_iScreenWidth;
		int m_iScreenHeight;
		int m_iScaleWidth;
		int m_iScaleHeight;
		int m_iBufferSize;
		RECT m_kRect;
		CHAR_INFO* m_pkScreenBuffer;
		CHAR_INFO* m_pkScaleBuffer;
		CHAR_INFO* m_pkBuffer;
		static oScreen* m_pkInstance;
	};
}