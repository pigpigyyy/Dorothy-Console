#include "oRenderController.h"
using namespace Dorothy;

oRenderController* oRenderController::m_pkInstance = NULL;

oRenderController::oRenderController():
m_BkColor(COLOR_NONE),
m_bEnabled(true)
{
	oIRender::SetZIndexListener(this);
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

void oRenderController::SetEnabled(bool enable)
{
	m_bEnabled = enable;
}

bool oRenderController::IsEnabled() const
{
	return m_bEnabled;
}

void oRenderController::Render()
{
	if (m_bZChanged)
	{
		oRenderController::SortZIndex();
	}
	int iSize = m_kList.size();
	oScreen::GetInstance()->Begin(m_BkColor);
	for (int i = 0;i < iSize;i++)
	{
		m_kList[i]->Render();
	}
	oScreen::GetInstance()->End();
}

void oRenderController::Register( oIRender* pkRender )
{
	if (pkRender->m_ID == ID_NONE)
	{
		pkRender->m_ID = m_kList.size();
		m_kList.push_back(pkRender);
		m_bZChanged = true;
	}
}

void oRenderController::UnRegister( oIRender* pkRender )
{
	int ID = pkRender->m_ID;
	if (ID != ID_NONE)
	{
		pkRender->m_ID = ID_NONE;
		int iLast = m_kList.size()-1;
		if (ID != iLast)
		{
			m_kList[ID] = m_kList[iLast];
			m_kList[iLast]->m_ID = ID;
			m_bZChanged = true;
		}
		m_kList.pop_back();
	}
}

oRenderController* oRenderController::GetInstance()
{
	return m_pkInstance;
}

void oRenderController::SortZIndex()
{
	m_bZChanged = false;
	int iSize = m_kList.size();
	for (int i = 1;i < iSize;i++)
	{
		oIRender* pkRender = m_kList[i];
		int low = 0, high = i-1;
		while (low <= high)
		{
			int mid = (low + high)>>1;
			if (pkRender->GetZIndex() < m_kList[mid]->GetZIndex())
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		for (int o = i-1;o >= low;o--)
		{
			int pos = o+1;
			m_kList[pos] = m_kList[o];
			m_kList[pos]->m_ID = pos;
		}
		if (low != i)
		{
			m_kList[low] = pkRender;
			m_kList[low]->m_ID = low;
		}
	}
}

void oRenderController::SetBackColor( oColor color )
{
	m_BkColor = color;
}