#pragma once

#include "oDataTypes.h"
#include "oIRender.h"
#include "oScreen.h"

namespace Dorothy
{
	class DLLEXPORT oCirclePaint:public oIRender
	{
	public:
		oCirclePaint();
		void Set(const oPoint& kCenter, int iRadius, oColor color, char ch = ' ');
		void SetCenter(const oPoint& kCenter);
		void SetRadius(int iRadius);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		oPoint m_kCenter;
		int m_iRadius;
		oColor m_Color;
		char m_Ch;
	};
}