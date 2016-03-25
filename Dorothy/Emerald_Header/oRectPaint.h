#pragma once

#include "oDataTypes.h"
#include "oIRender.h"
#include "oScreen.h"

namespace Dorothy
{
	class DLLEXPORT oRectPaint:public oIRender
	{
	public:
		oRectPaint();
		void Set(const RECT& rect, oColor color, char ch = ' ');
		void SetColor(oColor color);
		void SetRect(const RECT& rect);
		void SetChar(char ch);
	private:
		virtual void Render();
		RECT m_kRect;
		oColor m_Color;
		char m_Ch;
	};
}