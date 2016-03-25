#include "oZIndexListener.h"
using namespace Dorothy;

oZIndexListener::oZIndexListener()
:m_bZChanged(false){}

void oZIndexListener::NotifyZChange()
{
	m_bZChanged = true;
}