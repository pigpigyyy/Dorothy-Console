#pragma once

#include "oDataTypes.h"
#include "oIRender.h"
#include "oScreen.h"

namespace Dorothy
{
	class DLLEXPORT oLinePaint:public oIRender
	{
	public:
		oLinePaint();
		void Set(const oPoint& start,const oPoint& end, oColor color, char ch = ' ');
		void SetLine(const oPoint& start,const oPoint& end);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		oPoint m_kStart;
		oPoint m_kEnd;
		oColor m_Color;
		char m_Ch;
	};
}