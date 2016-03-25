#pragma once

#include "oDataTypes.h"
#include "oIRender.h"
#include "oScreen.h"

namespace Dorothy
{
	class DLLEXPORT oDotPaint:public oIRender
	{
	public:
		oDotPaint();
		void Set(const oPoint* pointList, oUInt number, oColor color, char ch = ' ');
		void SetPoint(const oPoint* pointList, oUInt number);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		const oPoint* m_pkPointList;
		int m_iNumber;
		oColor m_Color;
		char m_Ch;
	};
}