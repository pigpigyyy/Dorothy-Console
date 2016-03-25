#include "oIUpdate.h"
#include "oUpdateController.h"
using namespace Dorothy;

oIUpdate::oIUpdate():
m_ID(ID_NONE){}

oIUpdate::~oIUpdate()
{
	oIUpdate::UnRegister();
}

void oIUpdate::Register()
{
	if (m_ID == ID_NONE)
	{
		oUpdateController::GetInstance()->Register(this);
	}
}

void oIUpdate::UnRegister()
{
	if (m_ID != ID_NONE)
	{
		oUpdateController::GetInstance()->UnRegister(this);
	}
}

bool oIUpdate::IsRegistered() const
{
	return (m_ID != ID_NONE);
}

void oIUpdate::SetAutoManaged(bool autoManaged)
{
	oUpdateController::GetInstance()->SetEnabled(autoManaged);
}

bool oIUpdate::IsAutoManaged()
{
	return oUpdateController::GetInstance()->IsEnabled();
}
