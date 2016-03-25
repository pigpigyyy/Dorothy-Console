#pragma once
#include <vector>
using std::vector;
#include "oZIndexListener.h"
#include "oIRender.h"
#include "oScreen.h"

namespace Dorothy
{
	class oRenderController:public oZIndexListener
	{
	public:
		oRenderController();
		void Render();
		void Register(oIRender* pkRender);
		void UnRegister(oIRender* pkRender);
		void SetBackColor(oColor color);
		void SetEnabled(bool enable);
		bool IsEnabled() const;
		static oRenderController* GetInstance();
	private:
		bool m_bEnabled;
		oColor m_BkColor;
		void SortZIndex();
		vector<oIRender*> m_kList;
		static oRenderController* m_pkInstance;
	};
}