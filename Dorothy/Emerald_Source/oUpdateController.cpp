#include "oUpdateController.h"
#include <cassert>
using namespace Dorothy;

oUpdateController* oUpdateController::m_pkInstance = NULL;

oUpdateController::oUpdateController():
	m_bEnabled(true)
{
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

void oUpdateController::SetEnabled(bool enable)
{
	m_bEnabled = enable;
}

bool oUpdateController::IsEnabled() const
{
	return m_bEnabled;
}

void oUpdateController::Update()
{
	for (int i = 0;i < (int)m_kList.size();i++)
	{
		m_kList[i]->Update();
	}
}

void oUpdateController::Register( oIUpdate* pkUpdate )
{
	if (pkUpdate->m_ID == ID_NONE)
	{
		pkUpdate->m_ID = m_kList.size();
		m_kList.push_back(pkUpdate);
	}
}

void oUpdateController::UnRegister( oIUpdate* pkUpdate )
{
	int ID = pkUpdate->m_ID;
	if (ID != ID_NONE)
	{
		pkUpdate->m_ID = ID_NONE;
		int iLast = m_kList.size()-1;
		if (ID != iLast)
		{
			m_kList[ID] = m_kList[iLast];
			m_kList[iLast]->m_ID = ID;
		}
		m_kList.pop_back();
	}
}

oUpdateController* oUpdateController::GetInstance()
{
	return m_pkInstance;
}

