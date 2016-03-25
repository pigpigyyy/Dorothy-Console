#include "oIRender.h"
#include "oRenderController.h"
using namespace Dorothy;

oZIndexListener* oIRender::m_pkListener = NULL;

oIRender::oIRender( bool bVisible ):
m_iZ(0),
m_ID(ID_NONE)
{
	if (bVisible)
	{
		oIRender::SetVisible(V_VISIBLE);
	}
	else
	{
		m_Visibility = V_COLLAPSE;
	}
}

oIRender::~oIRender()
{
	oRenderController::GetInstance()->UnRegister(this);
}

void oIRender::SetZIndex( int iZ )
{
	m_iZ = iZ;
	m_pkListener->NotifyZChange();
}

void oIRender::SetVisible( oVisibility Visibility )
{
	switch (Visibility)
	{
	case V_VISIBLE:
		oRenderController::GetInstance()->Register(this);
		break;
	case V_COLLAPSE:
		oRenderController::GetInstance()->UnRegister(this);
		break;
	case V_HIDDEN:
		if (m_Visibility == V_COLLAPSE)
		{
			oRenderController::GetInstance()->Register(this);
		}
	default:
		break;
	}
	m_Visibility = Visibility;
}

void oIRender::SetVisible( bool bVisible )
{
	if (m_Visibility == V_COLLAPSE)
	{
		oRenderController::GetInstance()->Register(this);
	}
	m_Visibility = (bVisible ? V_VISIBLE : V_HIDDEN);
}

int oIRender::GetZIndex() const
{
	return m_iZ;
}

bool oIRender::IsVisible() const
{
	return (m_Visibility == V_VISIBLE);
}

void oIRender::SetZIndexListener( oZIndexListener* pkListener )
{
	m_pkListener = pkListener;
}

void oIRender::SetAutoManaged(bool autoManaged)
{
	oRenderController::GetInstance()->SetEnabled(autoManaged);
}

bool oIRender::IsAutoManaged()
{
	return oRenderController::GetInstance()->IsEnabled();
}
